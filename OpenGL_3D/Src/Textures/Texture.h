#pragma once

#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <iostream>
#include <vector>
#include "..\Assert.h"

class Texture
{
private:
	GLuint textureID = 0;
	int width = 0, height = 0, nrChannels = 0;

	enum ERRORS
	{
		INVALID_INTERNAL_FORMAT, INVALID_TEXTURE_PATH
	};
	const std::vector<std::string> errorStrings = { "INVALID_INTERNAL_FORMAT", "INVALID_TEXTURE_PATH" };
public:
	Texture(const std::string& texturePath);
	~Texture() = default;

	GLuint getHandle() const;

	void bind() const;
};

