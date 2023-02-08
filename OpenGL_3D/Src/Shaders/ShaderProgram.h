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
	std::unique_ptr<Shader> vertex = nullptr;
	std::unique_ptr<Shader> fragment = nullptr;

	enum ERRORS
	{
		LINKING, INVALID_SHADER_PATH, INVALID_SHADER_COUNT, INVALID_UNIFORM_NAME, INVALID_UNIFORM_VALUES
	};
	const std::vector<std::string> errorStrings = { "LINKING", "INVALID_SHADER_PATH", "INVALID_SHADER_COUNT",
		"INVALID_UNIFORM_NAME", "INVALID_UNIFORM_VALUES" };

public:
	//ShaderProgram(size_t count, GLuint* shaders);
	//ShaderProgram(size_t count, ...);
	//ShaderProgram(std::vector<Shader> shaderVector);
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~ShaderProgram();

	void update(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	void setBoolUniform(const std::string& uniformName, const std::vector<bool>& values);
	void setIntUniform(const std::string& uniformName, const std::vector<int>& values);
	void setFloatUniform(const std::string& uniformName, const std::vector<float>& values);
	void setMatrix4Uniform(const std::string& uniformName, const glm::mat4& values);

	void bind();
	int getHandle();
};