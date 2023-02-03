#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>

class VertexArray
{
private:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	size_t count = 0;
	std::vector<GLuint> offsets;

	enum ERRORS : int
	{
		INVALID_VERTICES_COUNT = 1, INVALID_VERTICES_POINTER, INVALID_OFFSETS
	};
	const char* const errors[64] = { "INVALID_VERTICES_COUNT", "INVALID_VERTICES_POINTER", "INVALID_OFFSETS" };
	void errorMsg(const char* message, unsigned int errorCode);
public:
	//VertexArray(size_t count, float* vertices);
	VertexArray(size_t count, float* vertices, std::vector<GLuint> offsets);
	VertexArray(size_t count, float* vertices, std::vector<GLuint> offsets, std::vector<GLuint> eboIndices);
	~VertexArray();

	void bind();
	void unbind();
};