#include "Assert.h"

void Assert::assertMsg(const std::string& file, const int line, const std::string& function, const std::string& message)
{
	std::cout << "ASSERT  >>   * FILE:       " << file << "\n";
	std::cout << "             * FUNCTION:   " << function << "\n";
	std::cout << "             * LINE:       " << line << "\n";
	std::cout << "             * MESSAGE:    " << message << std::endl;
}

void Assert::assertGL(const std::string& file, const int line, const std::string& function, const std::string& code)
{
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
		return;

	std::cout << "ASSERT  >>   * FILE:       " << file << "\n";
	std::cout << "             * FUNCTION:   " << function << "\n";
	std::cout << "             * LINE:       " << line << "\n";
	std::cout << "             * CODE:       " << code << "\n";
	std::cout << "             * ERROR:      " << error << std::endl;
}

void Assert::clearGLError()
{
	while (glGetError() != GL_NO_ERROR);
}