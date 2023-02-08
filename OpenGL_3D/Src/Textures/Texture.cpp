#include "Texture.h"

Texture::Texture(const std::string& texturePath)
{
	unsigned char* textureData = nullptr;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	stbi_set_flip_vertically_on_load(true);
	textureData = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	
	if (!textureData)
	{
		ASSERT_MSG(errorStrings[ERRORS::INVALID_TEXTURE_PATH]);
		return;
	}

	int internalFormat = 0;
	switch (nrChannels)
	{
	case 3:
		internalFormat = GL_RGB;
		break;
	case 4:
		internalFormat = GL_RGBA;
		break;
	default:
		ASSERT_MSG(errorStrings[ERRORS::INVALID_INTERNAL_FORMAT]);
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(textureData);
}

GLuint Texture::getHandle() const
{
	return textureID;
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + textureID - 1);
	glBindTexture(GL_TEXTURE_2D, textureID);
}