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

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	if (vertexShaderPath.empty())
		ASSERT_MSG(errorStrings[ERRORS::INVALID_SHADER_PATH] + vertexShaderPath);
	if (fragmentShaderPath.empty())
		ASSERT_MSG(errorStrings[ERRORS::INVALID_SHADER_PATH] + fragmentShaderPath);
	if (vertexShaderPath.empty() || fragmentShaderPath.empty())
		return;

	vertex.reset(new Shader(vertexShaderPath, GL_VERTEX_SHADER));
	fragment.reset(new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER));

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
		ASSERT_MSG(errorStrings[ERRORS::LINKING] + infoLog);
	}

	glDeleteShader(vertex->getHandle());
	glDeleteShader(fragment->getHandle());
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programID);
}

void ShaderProgram::update(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	int success = 0;
	char infoLog[512]{};

	if (vertexShaderPath.empty() && fragmentShaderPath.empty())
		return;

	glDeleteProgram(programID);
	programID = 0;

	if (!vertexShaderPath.empty())
	{
		vertex.reset(new Shader(vertexShaderPath, GL_VERTEX_SHADER));
	}
	if (!fragmentShaderPath.empty())
	{
		fragment.reset(new Shader(fragmentShaderPath, GL_FRAGMENT_SHADER));
	}

	programID = glCreateProgram();

	glAttachShader(programID, vertex->getHandle());
	glAttachShader(programID, fragment->getHandle());
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		ASSERT_MSG(errorStrings[ERRORS::LINKING] + infoLog);
	}

	glDeleteShader(vertex->getHandle());
	glDeleteShader(fragment->getHandle());
}

void ShaderProgram::bind()
{
	glUseProgram(programID);
}

int ShaderProgram::getHandle()
{
	return programID;
};

void ShaderProgram::setBoolUniform(const std::string& uniformName, const std::vector<bool>& values)
{
	int location = glGetUniformLocation(programID, uniformName.c_str());
	if (location == -1)
	{
		ASSERT_MSG(errorStrings[ERRORS::INVALID_UNIFORM_NAME] + uniformName);
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
		ASSERT_MSG(errorStrings[ERRORS::INVALID_UNIFORM_VALUES] + uniformName);
		return;
	}
}

void ShaderProgram::setIntUniform(const std::string& uniformName, const std::vector<int>& values)
{
	int location = glGetUniformLocation(programID, uniformName.c_str());
	if (location == -1)
	{
		ASSERT_MSG(errorStrings[ERRORS::INVALID_UNIFORM_NAME] + uniformName);
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
		ASSERT_MSG(errorStrings[ERRORS::INVALID_UNIFORM_VALUES] + uniformName);
		return;
	}
}

void ShaderProgram::setFloatUniform(const std::string& uniformName, const std::vector<float>& values)
{
	int location = glGetUniformLocation(programID, uniformName.c_str());
	if (location == -1)
	{
		ASSERT_MSG(errorStrings[ERRORS::INVALID_UNIFORM_NAME] + uniformName);
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
		ASSERT_MSG(errorStrings[ERRORS::INVALID_UNIFORM_VALUES] + uniformName);
		return;
	}
}

void ShaderProgram::setMatrix4Uniform(const std::string& uniformName, const glm::mat4& values)
{
	int location = glGetUniformLocation(programID, uniformName.c_str());
	if (location == -1)
	{
		ASSERT_MSG(errorStrings[ERRORS::INVALID_UNIFORM_NAME] + uniformName);
		return;
	}

	glUniformMatrix4fv(location, 1, GL_FALSE, &values[0][0]);
}