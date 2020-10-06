#pragma once
#include "vgl.h"
#include <string>
#include <vector>
#include <list>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef struct CubemapTexture
{
	GLenum type;
	std::string fileName;
};

class CubemapShader
{
public:
	CubemapShader();
	~CubemapShader();

	bool Init(const std::vector<CubemapTexture>& textures, int);
	bool LoadTextures(const std::vector<CubemapTexture>& textures);
	void SetMVMat(const glm::mat4& mat);
	void SetPMat(const glm::mat4& mat);
	void SetTime(const int);
	void SetMouse(const int, const int, const int, const int);
	void setResolution(const int, const int);
	void Render();
	void UseTexture(bool use);

	std::list<GLuint> shaderList;
	GLuint program;
	void Enable(void);
	void Disable(void);
	bool InitShader();
	bool AddShader(GLenum shaderType, std::string fileName);
	char** LoadShaderSource(const char* file);
	void FreeShaderSource(char** srcp);
	bool CheckShaderCompiled(GLuint shader);
	bool CheckProgramLinked(GLuint program);
	bool Finalize();
	GLuint GetUniformLocation(const GLchar* name);
	typedef struct _TextureData
	{
		_TextureData() : width(0), height(0), data(0) {}
		int width;
		int height;
		unsigned char* data;
	} TextureData;
	TextureData Load_png(const char* path, bool mirroredY = true);
	bool CheckGLError(void);

	GLuint mouseLocation;
	GLuint timeLocation;
	GLuint resolutionLocation;

	void CreateBox();
	void genPointSprite(GLuint);
	void drawPointSprite(GLuint, glm::mat4, int, int, int, int, int);

private:
	GLuint textureID;
	GLuint um4mvLocation;
	GLuint um4pLocation;
	GLuint vao, vbo, ebo;
};

