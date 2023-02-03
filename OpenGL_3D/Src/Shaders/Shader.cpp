#include "Shader.h"

Shader::Shader(const char* shaderPath, GLenum shaderType)
	:shaderPath(shaderPath)
{
	int success = 0;
	char infoLog[512]{};
	const char* shaderFile = nullptr;

	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
		shaderTypeName = _strdup("VERTEX");
		break;
	case GL_FRAGMENT_SHADER:
		shaderTypeName = _strdup("FRAGMENT");
		break;
	default:
		errorMsg(nullptr, ERRORS::INVALID_SHADER_TYPE);
		return;
	}

	if (!(shaderPath && strlen(shaderPath)))
	{
		errorMsg(nullptr, ERRORS::INVALID_SHADER_FILE);
		return;
	}

	std::ifstream file(shaderPath);
	std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	if (!(buffer.c_str() && strlen(buffer.c_str())))
	{
		errorMsg(nullptr, ERRORS::INVALID_SHADER_FILE);
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
		errorMsg(infoLog, ERRORS::COMPILING);
		return;
	}
}

Shader::~Shader()
{
	glDeleteShader(shaderID);
}

const char* Shader::getPath()
{
	return _strdup(shaderPath);
}

void Shader::errorMsg(const char* message, unsigned int errorCode)
{
	std::cout << "\n**************************************************" << std::endl;
	std::cout << "ERROR::SHADER";
	if (shaderTypeName)
		std::cout << "::" << shaderTypeName;

	if (errorCode)
		std::cout << "::" << errors[errorCode - 1];
	std::cout << std::endl;
	if (message && strlen(message))
		std::cout << message << std::endl;

	std::cout << "\n**************************************************" << std::endl;
}

char* Shader::shaderToString(const char* shaderPath)
{
	std::ifstream file(shaderPath);
	std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	if (buffer.c_str() && strlen(buffer.c_str()))
		return _strdup(buffer.c_str());
	return nullptr;
}