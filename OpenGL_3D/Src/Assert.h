#pragma once
#include <iostream>
#include <glad/glad.h>

#define ASSERT_MSG(message) Assert::assertMsg(__FILE__, __LINE__, __FUNCTION__, message)
#define ASSERT_GL(x) Assert::clearGLError();\
x;\
Assert::assertGL(__FILE__, __LINE__, __FUNCTION__, #x)

class Assert
{
private:
	Assert() = default;
	Assert(const Assert& original) = default;
	~Assert() = default;

public:
	static void assertMsg(const std::string& file, const int line, const std::string& function, const std::string& message);
	static void assertGL(const std::string& file, const int line, const std::string& function, const std::string& code);

	static void clearGLError();
};