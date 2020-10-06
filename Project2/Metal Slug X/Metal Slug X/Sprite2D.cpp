#include "Sprite2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

TextureData Load_png(const char* path)
{
	TextureData texture;
	int n;
	stbi_uc *data = stbi_load(path, &texture.width, &texture.height, &n, 4);
	if (data != NULL)
	{
		texture.data = new unsigned char[texture.width * texture.height * 4 * sizeof(unsigned char)];
		memcpy(texture.data, data, texture.width * texture.height * 4 * sizeof(unsigned char));
		// vertical-mirror image data
		for (size_t i = 0; i < texture.width; i++)
		{
			for (size_t j = 0; j < texture.height / 2; j++)
			{
				for (size_t k = 0; k < 4; k++) {
					std::swap(texture.data[(j * texture.width + i) * 4 + k], texture.data[((texture.height - j - 1) * texture.width + i) * 4 + k]);
				}
			}
		}
		stbi_image_free(data);
	}
	return texture;
}

Sprite2D::Sprite2D()
{
	
}


Sprite2D::~Sprite2D()
{
}

bool Sprite2D::Init(std::string fileName, int a)
{
	return false;
}

bool Sprite2D::Init(std::string fileName, int width, int height, int totalSprite)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
	//glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32F, width, height, totalSprite);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA32F, width, height, totalSprite);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glPixelStorei(GL_UNPACK_ROW_LENGTH, width);

	for (int i = 0; i < totalSprite; i++)
	{
		std::stringstream stream;
		stream << fileName << i << ".png";
		std::string subFileName = "";
		stream >> subFileName;
		TextureData tdata = Load_png(subFileName.c_str());
		if (tdata.data != nullptr)
		{
			subWidth = tdata.width;
			subHeight = tdata.height;
			//GLubyte *data = tdata.data + (tdata.width * height + width) * 4;
			GLubyte *data = tdata.data;
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
			delete tdata.data;
		}
		else
		{
			puts(subFileName.c_str());
			puts("Can't find png picture");
		}
	}
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	return true;
}

glm::mat4 Sprite2D::GetModelMat()
{
	return scaleMat;
}

float Sprite2D::GetAspect()
{
	return spriteAspect;
}

float Sprite2D::GetFPS()
{
	return spriteFPS;
}

int Sprite2D::GetCount()
{
	return spriteCount;
}

void Sprite2D::Enable()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
}

void Sprite2D::Disable()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}
