#include "ShaderProgram.h"

/*
ShaderProgram::ShaderProgram(size_t count, GLuint* shaders)
{
	int success = 0;
	char infoLog[512]{};

	if (count <= 0)
	{
		errorMsg(nullptr, ERRORS::INVALID_SHADER_COUNT);
		return;
	}
	if (!shaders)
	{
		errorMsg(nullptr, ERRORS::INVALID_SHADER_POINTER);
		return;
	}

	programID = glCreateProgram();

	for (int i = 0; i < count; i++)
		glAttachShader(programID, shaders[i]);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		errorMsg(infoLog, ERRORS::LINKING);
	}

	for (int i = 0; i < count; i++)
		glDeleteShader(shaders[i]);
}

ShaderProgram::ShaderProgram(size_t count, ...)
{
	int success = 0;
	char infoLog[512]{};
	va_list shaders;

	if (count <= 0)
	{
		errorMsg(nullptr, ERRORS::INVALID_SHADER_COUNT);
		return;
	}

	programID = glCreateProgram();

	va_start(shaders, count);
	for (int i = 0; i < count; i++)
		glAttachShader(programID, (va_arg(shaders, Shader)).getHandle());
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		errorMsg(infoLog, ERRORS::LINKING);
	}

	va_start(shaders, count);
	for (int i = 0; i < count; i++)
		glDeleteShader((va_arg(shaders, Shader)).getHandle());
	va_end(shaders);
}
*/

/*
ShaderProgram::ShaderProgram(std::vector<Shader> shaderVector)
{
	int success = 0;
	char infoLog[512]{};

	if (shaderVector.size() <= 0)
	{
		errorMsg(nullptr, ERRORS::INVALID_SHADER_COUNT);
		return;
	}

	programID = glCreateProgram();

	for (auto& shader : shaderVector)
		glAttachShader(programID, shader.getHandle());
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		errorMsg(infoLog, ERRORS::LINKING);
	}

	for (auto& shader : shaderVector)
		glDeleteShader(shader.getHandle());
}
*/

ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	vertex = new Shader(vertexShaderPath, GL_VERTEX_SHADER);
	fragment = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	int success = 0;
	char infoLog[512]{};

	programID = glCreateProgram();

	glAttachShader(programID, vertex->getHandle());
	glAttachShader(programID, fragment->getHandle());
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		errorMsg(infoLog, ERRORS::LINKING);
	}

	glDeleteShader(vertex->getHandle());
	glDeleteShader(fragment->getHandle());
}

ShaderProgram::~ShaderProgram()
{
	delete vertex;
	delete fragment;

	glDeleteProgram(programID);
}

void ShaderProgram::update(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	int success = 0;
	char infoLog[512]{};

	glDeleteProgram(programID);
	programID = 0;

	const char* vertexPath = vertex->getPath();
	delete vertex;
	if (vertexShaderPath)
		vertex = new Shader(vertexShaderPath, GL_VERTEX_SHADER);
	else
		vertex = new Shader(vertexPath, GL_VERTEX_SHADER);

	const char* fragmentPath = fragment->getPath();
	delete fragment;
	if (fragmentShaderPath)
		fragment = new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER);
	else
		fragment = new Shader(fragmentPath, GL_FRAGMENT_SHADER);

	programID = glCreateProgram();

	glAttachShader(programID, vertex->getHandle());
	glAttachShader(programID, fragment->getHandle());
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		errorMsg(infoLog, ERRORS::LINKING);
	}

	glDeleteShader(vertex->getHandle());
	glDeleteShader(fragment->getHandle());
}

void ShaderProgram::use()
{
	glUseProgram(programID);
}

int ShaderProgram::getHandle()
{
	return programID;
};

void ShaderProgram::setBoolUniform(const char* uniformName, std::vector<bool> values)
{
	int location = glGetUniformLocation(programID, uniformName);
	if (location == -1)
	{
		errorMsg(uniformName, ERRORS::INVALID_UNIFORM_NAME);
		return;
	}

	switch (values.size())
	{
	case 1:
		glUniform1i(location, values.at(0));
		break;
	case 2:
		glUniform2i(location, values.at(0), values.at(1));
		break;
	case 3:
		glUniform3i(location, values.at(0), values.at(1), values.at(2));
		break;
	case 4:
		glUniform4i(location, values.at(0), values.at(1), values.at(2), values.at(3));
		break;
	default:
		errorMsg(uniformName, ERRORS::INVALID_UNIFORM_VALUES);
		return;
	}
}

void ShaderProgram::setIntUniform(const char* uniformName, std::vector<int> values)
{
	int location = glGetUniformLocation(programID, uniformName);
	if (location == -1)
	{
		errorMsg(uniformName, ERRORS::INVALID_UNIFORM_NAME);
		return;
	}

	switch (values.size())
	{
	case 1:
		glUniform1i(location, values.at(0));
		break;
	case 2:
		glUniform2i(location, values.at(0), values.at(1));
		break;
	case 3:
		glUniform3i(location, values.at(0), values.at(1), values.at(2));
		break;
	case 4:
		glUniform4i(location, values.at(0), values.at(1), values.at(2), values.at(3));
		break;
	default:
		errorMsg(uniformName, ERRORS::INVALID_UNIFORM_VALUES);
		return;
	}
}

void ShaderProgram::setFloatUniform(const char* uniformName, std::vector<float> values)
{
	int location = glGetUniformLocation(programID, uniformName);
	if (location == -1)
	{
		errorMsg(uniformName, ERRORS::INVALID_UNIFORM_NAME);
		return;
	}

	switch (values.size())
	{
	case 1:
		glUniform1f(location, values.at(0));
		break;
	case 2:
		glUniform2f(location, values.at(0), values.at(1));
		break;
	case 3:
		glUniform3f(location, values.at(0), values.at(1), values.at(2));
		break;
	case 4:
		glUniform4f(location, values.at(0), values.at(1), values.at(2), values.at(3));
		break;
	default:
		errorMsg(uniformName, ERRORS::INVALID_UNIFORM_VALUES);
		return;
	}
}

void ShaderProgram::setMatrix4Uniform(const char* uniformName, std::vector<glm::mat4> values)
{
	int location = glGetUniformLocation(programID, uniformName);
	if (location == -1)
	{
		errorMsg(uniformName, ERRORS::INVALID_UNIFORM_NAME);
		return;
	}
	if (values.size() <= 0)
	{
		errorMsg(uniformName, ERRORS::INVALID_UNIFORM_VALUES);
		return;
	}

	glUniformMatrix4fv(location, static_cast<GLsizei>(values.size()), GL_FALSE, glm::value_ptr(values.at(0)));
}

void ShaderProgram::errorMsg(const char* message, unsigned int errorCode)
{
	std::cout << "\n**************************************************" << std::endl;
	std::cout << "ERROR::SHADER_PROGRAM";

	if (errorCode)
		std::cout << "::" << errors[errorCode];
	std::cout << std::endl;
	if (message && strlen(message))
		std::cout << message << std::endl;

	std::cout << "\n**************************************************" << std::endl;
}