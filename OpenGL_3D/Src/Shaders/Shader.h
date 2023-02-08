#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "..\Assert.h"

class Shader
{
private:
	GLuint shaderID = 0;
	std::string shaderPath;
	std::string shaderTypeName;

	enum ERRORS
	{
		INVALID_SHADER_FILE, INVALID_SHADER_TYPE, COMPILING
	};
	const std::vector<std::string> errorStrings = { "INVALID_SHADER_FILE", "INVALID_SHADER_TYPE", "COMPILING", "INVALID_PROGRAM" };

public:
	Shader(const std::string& shaderPath, GLenum shaderType);
	~Shader();

	GLuint getHandle() const;
	std::string getPath() const;

	static std::string shaderToString(const std::string& shaderPath);
};