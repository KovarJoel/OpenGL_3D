#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "Assert.h"

class VertexArray
{
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	std::vector<GLuint> offsets;

	enum ERRORS
	{
		INVALID_VERTICES, INVALID_OFFSETS
	};
	const std::vector<std::string> errorStrings = { "INVALID_VERTICES", "INVALID_OFFSETS" };

public:
	VertexArray(const std::vector<float>& vertices, const std::vector<GLuint>& offsets);
	VertexArray(const std::vector<float>& vertices, const std::vector<GLuint>& offsets, const std::vector<GLuint>& eboIndices);
	~VertexArray();

	void bind() const;
	void unbind() const;
};