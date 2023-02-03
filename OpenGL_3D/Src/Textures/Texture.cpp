#include "Texture.h"

Texture::Texture(const char* texturePath)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	stbi_set_flip_vertically_on_load(true);
	textureData = stbi_load(texturePath, &width, &height, &nrChannels, 0);

	if (!textureData)
	{
		errorMsg(nullptr, ERRORS::INVALID_TEXTURE_PATH);
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
		break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(textureData);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + textureID - 1);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::errorMsg(const char* message, unsigned int errorCode)
{
	std::cout << "\n**************************************************" << std::endl;
	std::cout << "ERROR::TEXTURE";

	if (errorCode)
		std::cout << "::" << errors[errorCode];
	std::cout << std::endl;
	if (message && strlen(message))
		std::cout << message << std::endl;

	std::cout << "\n**************************************************" << std::endl;
}