#include "Shader.h"

Shader::Shader(const std::string& shaderPath, GLenum shaderType)
	:shaderPath(shaderPath)
{
	int success = 0;
	char infoLog[512]{};
	const char* shaderFile = nullptr;

	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		shaderTypeName = "VERTEX";
		break;
	case GL_FRAGMENT_SHADER:
		shaderTypeName = "FRAGMENT";
		break;
	default:
		ASSERT_MSG(errorStrings[ERRORS::INVALID_SHADER_TYPE]);
		return;
	}

	if (shaderPath.empty() || !shaderPath.size())
	{
		ASSERT_MSG(errorStrings[ERRORS::INVALID_SHADER_FILE]);
		return;
	}

	std::ifstream file(shaderPath);
	std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	if (buffer.empty() || !buffer.size())
	{
		ASSERT_MSG(errorStrings[ERRORS::INVALID_SHADER_FILE]);
		return;
	}
	shaderFile = buffer.c_str();

	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderFile, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		ASSERT_MSG(errorStrings[ERRORS::COMPILING] + infoLog);
		return;
	}
}

Shader::~Shader()
{
	glDeleteShader(shaderID);
}

GLuint Shader::getHandle() const
{
	return shaderID;
}

std::string Shader::getPath() const
{
	return shaderPath;
}

std::string Shader::shaderToString(const std::string& shaderPath)
{
	std::ifstream file(shaderPath);
	std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	if (buffer.empty() || !buffer.size())
	{
		ASSERT_MSG("INVALID_SHADER_FILE");
		return std::string();
	}
	return buffer;
}