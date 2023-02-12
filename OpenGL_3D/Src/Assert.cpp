#include "Assert.h"

void Assert::assertMsg(const std::string& file, const int line, const std::string& function, const std::string& message)
{
	std::string msg = message;
	lineSplit(msg);

	std::cout << "ASSERT  >>   * FILE:       " << file << "\n";
	std::cout << "             * FUNCTION:   " << function << "\n";
	std::cout << "             * LINE:       " << line << "\n";
	std::cout << "             * MESSAGE:    " << msg << std::endl;
}

void Assert::assertGL(const std::string& file, const int line, const std::string& function, const std::string& code)
{
	GLenum error = glGetError();
	if (error == GL_NO_ERROR)
		return;

	std::string msg = code;
	lineSplit(msg);
	
	std::cout << "ASSERT  >>   * FILE:       " << file << "\n";
	std::cout << "             * FUNCTION:   " << function << "\n";
	std::cout << "             * LINE:       " << line << "\n";
	std::cout << "             * CODE:       " << code << "\n";
	std::cout << "             * ERROR:      " << msg << std::endl;
}

void Assert::clearGLError()
{
	while (glGetError() != GL_NO_ERROR);
}

void Assert::lineSplit(std::string& string)
{
	int find = 0, lastFind = 0;

	if (string.at(string.size() - 1) == '\n')
		string.resize(string.size() - 1);

	while (true)
	{
		if (lastFind + 1 > string.size())
			break;

		find = string.find("\n", lastFind + 1);
		if (find <= lastFind)
			break;
		lastFind = find;
		string.replace(find, 1, "\n                           ");
	}
}