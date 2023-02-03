#include "VertexArray.h"
/*
VertexArray::VertexArray(size_t count, float* vertices)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
*/

VertexArray::VertexArray(size_t count, float* vertices, std::vector<GLuint> offsets)
	:count(count), offsets(offsets)
{
	if (count <= 0)
	{
		errorMsg(nullptr, ERRORS::INVALID_VERTICES_COUNT);
		return;
	}
	if (!vertices)
	{
		errorMsg(nullptr, ERRORS::INVALID_VERTICES_POINTER);
		return;
	}
	if (offsets.size() <= 0)
	{
		errorMsg(nullptr, ERRORS::INVALID_OFFSETS);
		return;
	}
	for (auto& offset : offsets)
	{
		if (offset > 4 || offset <= 0)
		{
			errorMsg(nullptr, ERRORS::INVALID_OFFSETS);
			return;
		}
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	int stride = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		stride += offsets.at(i);
	}
	stride *= sizeof(vertices[0]);

	int voidPointerValue = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		if (i > 0)
			voidPointerValue += offsets.at(i - 1);
		glVertexAttribPointer(i, offsets.at(i), GL_FLOAT, GL_FALSE, stride, (void*)(voidPointerValue * sizeof(vertices[0])));
		glEnableVertexAttribArray(i);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

VertexArray::VertexArray(size_t count, float* vertices, std::vector<GLuint> offsets, std::vector<GLuint> eboIndices)
	:count(count), offsets(offsets)
{
	if (count <= 0)
	{
		errorMsg(nullptr, ERRORS::INVALID_VERTICES_COUNT);
		return;
	}
	if (!vertices)
	{
		errorMsg(nullptr, ERRORS::INVALID_VERTICES_POINTER);
		return;
	}
	if (offsets.size() <= 0)
	{
		errorMsg(nullptr, ERRORS::INVALID_OFFSETS);
		return;
	}
	for (auto& offset : offsets)
	{
		if (offset > 4 || offset <= 0)
		{
			errorMsg(nullptr, ERRORS::INVALID_OFFSETS);
			return;
		}
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboIndices.size() * sizeof(eboIndices.at(0)), &eboIndices[0], GL_STATIC_DRAW);
	
	int stride = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		stride += offsets.at(i);
	}
	stride *= sizeof(vertices[0]);

	int voidPointerValue = 0;
	for (int i = 0; i < offsets.size(); i++)
	{
		if (i > 0)
			voidPointerValue += offsets.at(i - 1);
		glVertexAttribPointer(i, offsets.at(i), GL_FLOAT, GL_FALSE, stride, (void*)(voidPointerValue * sizeof(vertices[0])));
		glEnableVertexAttribArray(i);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void VertexArray::bind()
{
	glBindVertexArray(VAO);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::errorMsg(const char* message, unsigned int errorCode)
{
	std::cout << "\n**************************************************" << std::endl;
	std::cout << "ERROR::VERTEX_ARRAY";

	if (errorCode)
		std::cout << "::" << errors[errorCode - 1];
	std::cout << std::endl;
	if (message && strlen(message))
		std::cout << message << std::endl;

	std::cout << "\n**************************************************" << std::endl;
}