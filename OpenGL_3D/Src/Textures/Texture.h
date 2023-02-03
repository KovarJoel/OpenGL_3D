#pragma once

#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <iostream>

class Texture
{
private:
	GLuint textureID = 0;
	int width = 0, height = 0, nrChannels = 0;
	unsigned char* textureData = nullptr;

	enum ERRORS : int
	{
		INVALID_INTERNAL_FORMAT, INVALID_TEXTURE_PATH
	};
	const char* const errors[64] = { "INVALID_INTERNAL_FORMAT", "INVALID_TEXTURE_PATH" };
	void errorMsg(const char* message, unsigned int errorCode);
public:
	Texture(const char* texturePath);

	int getHandle() { return textureID; };

	void bind();
};

