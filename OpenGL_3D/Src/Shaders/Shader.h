#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <vector>

class Shader
{
private:
	GLuint shaderID = 0;
	const char* shaderPath = nullptr;
	char* shaderTypeName = nullptr;

	enum ERRORS : int
	{
		INVALID_SHADER_FILE = 1, INVALID_SHADER_TYPE, COMPILING
	};
	const char* const errors[64] = { "INVALID_SHADER_FILE", "INVALID_SHADER_TYPE", "COMPILING", "INVALID_PROGRAM" };
	void errorMsg(const char* message, unsigned int errorCode);

public:
	Shader(const char* shaderPath, GLenum shaderType);
	~Shader();

	GLuint getHandle() { return shaderID; };
	const char* getPath();

	static char* shaderToString(const char* shaderPath);
};