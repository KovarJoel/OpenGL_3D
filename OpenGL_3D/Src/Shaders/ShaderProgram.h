#pragma once

#include <glad/glad.h>
#include <iostream>
//#include <stdarg.h>
//#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class ShaderProgram
{
private:
	GLuint programID = 0;
	Shader* vertex = nullptr;
	Shader* fragment = nullptr;

	enum ERRORS : int
	{
		LINKING = 1, INVALID_SHADER_POINTER, INVALID_SHADER_COUNT, INVALID_UNIFORM_NAME, INVALID_UNIFORM_VALUES
	};
	const char* const errors[64] = { "LINKING", "INVALID_SHADER_POINTER", "INVALID_SHADER_COUNT",
		"INVALID_UNIFORM_NAME", "INVALID_UNIFORM_VALUES" };
	void errorMsg(const char* message, unsigned int errorCode);

public:
	//ShaderProgram(size_t count, GLuint* shaders);
	//ShaderProgram(size_t count, ...);
	//ShaderProgram(std::vector<Shader> shaderVector);
	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();

	void update(const char* vertexShaderPath, const char* fragmentShaderPath);

	void setBoolUniform(const char* uniformName, std::vector<bool> values);
	void setIntUniform(const char* uniformName, std::vector<int> values);
	void setFloatUniform(const char* uniformName, std::vector<float> values);
	void setMatrix4Uniform(const char* uniformName, glm::mat4 values);

	void bind();
	int getHandle();
};