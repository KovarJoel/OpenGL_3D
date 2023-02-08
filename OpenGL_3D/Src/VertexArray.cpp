#include "VertexArray.h"

VertexArray::VertexArray(const std::vector<float>& vertices, const std::vector<GLuint>& offsets)
	:offsets(offsets)
{
	if (vertices.empty())
	{
		ASSERT_MSG(errorStrings.at(ERRORS::INVALID_VERTICES));
		return;
	}
	if (offsets.empty())
	{
		ASSERT_MSG(errorStrings.at(ERRORS::INVALID_OFFSETS));
		return;
	}
	for (const auto& offset : offsets)
	{
		if (offset > 4 || offset <= 0)
		{
			ASSERT_MSG(errorStrings.at(ERRORS::INVALID_OFFSETS));
			return;
		}
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	std::vector<float> test = { 1.0f, 2.0f };

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices.at(0)), &vertices.at(0), GL_STATIC_DRAW);

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

VertexArray::VertexArray(const std::vector<float>& vertices, const std::vector<GLuint>& offsets, const std::vector<GLuint>& eboIndices)
	:offsets(offsets)
{
	if (vertices.empty())
	{
		ASSERT_MSG(errorStrings.at(ERRORS::INVALID_VERTICES));
		return;
	}
	if (offsets.empty())
	{
		ASSERT_MSG(errorStrings.at(ERRORS::INVALID_OFFSETS));
		return;
	}
	for (const auto& offset : offsets)
	{
		if (offset > 4 || offset <= 0)
		{
			ASSERT_MSG(errorStrings.at(ERRORS::INVALID_OFFSETS));
			return;
		}
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices.at(0)), &vertices.at(0), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboIndices.size() * sizeof(eboIndices.at(0)), &eboIndices.at(0), GL_STATIC_DRAW);
	
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

void VertexArray::bind() const
{
	glBindVertexArray(VAO);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}