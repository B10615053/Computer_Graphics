#include "CubemapShader.h"
#pragma warning(disable:4996)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string fragmentShaderList[] = {
	"cubemap.fs.glsl",
	"cubemap.fs.glsl",
	"sceneShader0.fs.glsl", // Daze
	"sceneShader1.fs.glsl", // Smile
	"sceneShader2.fs.glsl", // Dark clouds (discarded)
	"sceneShader3.fs.glsl", // Sunshine
	"sceneShader4.fs.glsl", // Sine waves
	"sceneShader5.fs.glsl", // Black hole
	"sceneShader6.fs.glsl", // Shining star
	"sceneShader7.fs.glsl", // Distorted world
	"sceneShader8.fs.glsl", // Noise
	"sceneShader9.fs.glsl"
};

CubemapShader::CubemapShader()
{
}


CubemapShader::~CubemapShader()
{
}

bool CubemapShader::Init(const std::vector<CubemapTexture>& textures, int option)
{
	if (!InitShader())
	{
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "cubemap.vs.glsl")) {
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, fragmentShaderList[option]))
	{
		return false;
	}

	if (!Finalize())
	{
		return false;
	}

	um4mvLocation = GetUniformLocation("um4mv");
	if (um4mvLocation == -1)
	{
		puts("Get uniform loaction error: um4mv");
		return false;
	}

	um4pLocation = GetUniformLocation("um4p");
	if (um4pLocation == -1)
	{
		puts("Get uniform loaction error: um4p");
		return false;
	}

	timeLocation = GetUniformLocation("time");
	mouseLocation = GetUniformLocation("mouse");
	resolutionLocation = GetUniformLocation("resolution");

	CreateBox();

	return LoadTextures(textures);
}

void CubemapShader::SetMVMat(const glm::mat4& mat)
{
	glUniformMatrix4fv(um4mvLocation, 1, GL_FALSE, glm::value_ptr(mat));
}

void CubemapShader::SetPMat(const glm::mat4& mat)
{
	glUniformMatrix4fv(um4pLocation, 1, GL_FALSE, glm::value_ptr(mat));
}

void CubemapShader::SetTime(const int frameCounter)
{
	glUniform1f(timeLocation, (float)frameCounter);
}

void CubemapShader::SetMouse(const int x, const int y, const int w, const int h)
{
	// range: 0.0 - 1.0
	float fx = (((((float)x + ((float)w / 2.0f)) / ((float)w / 2.0f)) - 2.0f) + 1.0f) / 2.0f;
	float fy = (((((float)y + ((float)h / 2.0f)) / ((float)h / 2.0f)) - 2.0f) + 1.0f) / 2.0f;
	glUniform2f(mouseLocation, fx, fy);
}

void CubemapShader::setResolution(const int w, const int h) {
	glUniform2f(resolutionLocation, (float)w, (float)h);
}

void CubemapShader::Render()
{
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glBindVertexArray(0);
}

void CubemapShader::UseTexture(bool use)
{
	if (use)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	}
	else
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}

bool CubemapShader::LoadTextures(const std::vector<CubemapTexture>& textures)
{
	if (textures.size() != 6)
	{
		return false;
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (int i = 0; i < textures.size(); ++i)
	{
		TextureData texData = Load_png(textures[i].fileName.c_str());
		if (texData.data != nullptr)
		{
			printf("Load texture file %s...\n", textures[i].fileName.c_str());
			glTexImage2D(textures[i].type, 0, GL_RGBA, texData.width, texData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData.data);
			delete[] texData.data;
		}
		else
		{
			printf("Load texture file error %s\n", textures[i].fileName.c_str());
			return false;
		}
	}

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return CheckGLError();
}

void CubemapShader::CreateBox()
{
	// Vertex data
	float vertices[] = {
		-0.5, -0.5, -0.5,
		0.5, -0.5, -0.5,
		0.5, 0.5, -0.5,
		-0.5, 0.5, -0.5,
		-0.5, -0.5, 0.5,
		0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,
		-0.5, 0.5, 0.5
	};

	// Index data
	int indices[] = {
		// posx
		1, 5, 6,
		6, 2, 1,
		// negx
		4, 0, 3,
		3, 7, 4,
		// posy
		3, 2, 6,
		6, 7, 3,
		// neg y
		4, 5, 1,
		1, 0, 4,
		// posz
		5, 4, 7,
		7, 6, 5,
		// negz
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void CubemapShader::Enable()
{
	glUseProgram(program);
}
void CubemapShader::Disable()
{
	glUseProgram(0);
}

bool CubemapShader::InitShader()
{
	program = glCreateProgram();
	if (program == 0)
	{
		puts("Create program error\n");
		return false;
	}
	return true;
}
bool CubemapShader::AddShader(GLenum shaderType, std::string fileName)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		printf("Create shader error: %d\n", shaderType);
		return false;
	}

	shaderList.push_back(shader);

	char **shaderSource = LoadShaderSource((fileName).c_str());

	glShaderSource(shader, 1, (const char **)shaderSource, NULL);
	FreeShaderSource(shaderSource);

	glCompileShader(shader);
	bool isCompiled = CheckShaderCompiled(shader);
	if (!isCompiled)
	{
		return false;
	}

	glAttachShader(program, shader);

	return true;
}
//Read shader file
char** CubemapShader::LoadShaderSource(const char* file)
{
	FILE* fp = fopen(file, "rb");
	fseek(fp, 0, SEEK_END);
	long sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *src = new char[sz + 1];
	fread(src, sizeof(char), sz, fp);
	src[sz] = '\0';
	GLchar **srcp = new char*[1];
	srcp[0] = src;
	return srcp;
}
//Release 2-dimension array
void CubemapShader::FreeShaderSource(char** srcp)
{
	delete srcp[0];
	delete srcp;
}
bool CubemapShader::CheckShaderCompiled(GLuint shader)
{
	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		GLchar* errorLog = new GLchar[maxLength];
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

		printf("%s\n", errorLog);
		delete[] errorLog;

		return false;
	}

	return true;
}
bool CubemapShader::CheckProgramLinked(GLuint program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {

		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar *errorLog = new GLchar[maxLength];
		glGetProgramInfoLog(program, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Program link error: %s\n", errorLog);

		return false;
	}
	return true;
}

bool CubemapShader::Finalize()
{
	glLinkProgram(program);
	bool isLinked = CheckProgramLinked(program);

	for (std::list<GLuint>::iterator it = shaderList.begin(); it != shaderList.end(); ++it)
	{
		glDetachShader(program, *it);
		glDeleteShader(*it);
	}
	shaderList.clear();

	return isLinked;
}
GLuint CubemapShader::GetUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(program, name);
}
CubemapShader::TextureData CubemapShader::Load_png(const char* path, bool mirroredY)
{
	TextureData texture;
	int n;
	stbi_uc *data = stbi_load(path, &texture.width, &texture.height, &n, 4);
	if (data != NULL)
	{
		texture.data = new unsigned char[texture.width * texture.height * 4 * sizeof(unsigned char)];
		memcpy(texture.data, data, texture.width * texture.height * 4 * sizeof(unsigned char));
		// vertical-mirror image data
		if (mirroredY)
		{
			for (size_t i = 0; i < texture.width; i++)
			{
				for (size_t j = 0; j < texture.height / 2; j++)
				{
					for (size_t k = 0; k < 4; k++) {
						std::swap(texture.data[(j * texture.width + i) * 4 + k], texture.data[((texture.height - j - 1) * texture.width + i) * 4 + k]);
					}
				}
			}
		}
		stbi_image_free(data);
	}
	return texture;
}
bool CubemapShader::CheckGLError(void)
{
	GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		const GLubyte* errString = gluErrorString(errCode);
		printf("%s\n", errString);

		return false;
	}
	return true;
}

GLuint pointSpriteVAO, pointSpriteVBO;
GLint pointSpriteProjectLocation, pointSpriteTimeLocation, pointSpriteMouseLocation, pointSpriteResolutionLocation, plusOrMinusLocation;
GLuint m_texture;
static unsigned int seed = 0x13371337;

static inline float random_float() {
	float res;
	unsigned int tmp;

	seed *= 16807;
	tmp = seed ^ (seed >> 4) ^ (seed << 15);
	*((unsigned int *)&res) = (tmp >> 9) | 0x3F800000;

	return (res - 1.0f);
}

enum {
	NUM_STARS = 5000
};

void CubemapShader::genPointSprite(GLuint program) {
	glGenVertexArrays(1, &pointSpriteVAO);
	glBindVertexArray(pointSpriteVAO);

	pointSpriteProjectLocation = glGetUniformLocation(program, "proj_matrix");
	pointSpriteTimeLocation = glGetUniformLocation(program, "time");
	pointSpriteMouseLocation = glGetUniformLocation(program, "mouse");
	pointSpriteResolutionLocation = glGetUniformLocation(program, "resolution");
	plusOrMinusLocation = glGetUniformLocation(program, "plusOrMinus");

	struct star_t {
		glm::vec3     position;
		glm::vec3     color;
	};

	glGenBuffers(1, &pointSpriteVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pointSpriteVBO);
	glBufferData(GL_ARRAY_BUFFER, NUM_STARS * sizeof(star_t), NULL, GL_STATIC_DRAW);

	star_t * star = (star_t *)glMapBufferRange(GL_ARRAY_BUFFER, 0, NUM_STARS * sizeof(star_t), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	for (int i = 0; i < NUM_STARS; i++) {
		star[i].position[0] = (random_float() * 2.0f - 1.0f) * 100.0f;
		star[i].position[1] = (random_float() * 2.0f - 1.0f) * 100.0f;
		star[i].position[2] = random_float();

		star[i].color[0] = 0.8f + random_float() * 0.2f;
		star[i].color[1] = 0.8f + random_float() * 0.2f;
		star[i].color[2] = 0.8f + random_float() * 0.2f;
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(star_t), NULL);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(star_t), (void *)sizeof(glm::vec3));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);

	TextureData tdata = Load_png("star.png");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tdata.width, tdata.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tdata.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void CubemapShader::drawPointSprite(GLuint program, glm::mat4 proj_matrix, int x, int y, int w, int h, int plusOrMinus) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Update shaders' input variable
	///////////////////////////
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	static const GLfloat one = 1.0f;

	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glBindVertexArray(pointSpriteVAO);
	glUseProgram(program);

	float f_timer_cnt = glutGet(GLUT_ELAPSED_TIME);
	float currentTime = f_timer_cnt * 0.001f;

	currentTime *= 0.1f;
	currentTime -= floor(currentTime);

	// um: time
	glUniform1f(pointSpriteTimeLocation, currentTime);

	// um: projection
	glUniformMatrix4fv(pointSpriteProjectLocation, 1, GL_FALSE, &proj_matrix[0][0]);
	
	// um: mouse
	// range: 0.0 - 1.0
	float fx = (((((float)x + ((float)w / 2.0f)) / ((float)w / 2.0f)) - 2.0f) + 1.0f) / 2.0f;
	float fy = (((((float)y + ((float)h / 2.0f)) / ((float)h / 2.0f)) - 2.0f) + 1.0f) / 2.0f;
	glUniform2f(pointSpriteMouseLocation, fx, fy);

	// um: resolution
	glUniform2f(pointSpriteResolutionLocation, (float)w, (float)h);

	// um: plus or minus
	glUniform1i(plusOrMinusLocation, plusOrMinus);

	glEnable(GL_POINT_SPRITE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glDrawArrays(GL_POINTS, 0, NUM_STARS);
	///////////////////////////
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	
}