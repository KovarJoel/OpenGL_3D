#include "Cube.h"

Cube::Cube(float length, const char* texturePath)
{	
	vertices.reserve(40);
	setSize(length);

	VAO = new VertexArray(vertices.size(), &vertices[0], { 3, 2 }, indices);
	text = new Texture(texturePath);
}

Cube::~Cube()
{
	delete VAO;
	delete text;
}

void Cube::setSize(float length)
{
	size = length / 2.0f;

	vertices = {
		-size, +size, +size, 0.0f, 1.0f,
		+size, +size, +size, 1.0f, 1.0f,
		+size, -size, +size, 1.0f, 0.0f,
		-size, -size, +size, 0.0f, 0.0f,

		-size, +size, -size, 0.0f, 1.0f,
		+size, +size, -size, 1.0f, 1.0f,
		+size, -size, -size, 1.0f, 0.0f,
		-size, -size, -size, 0.0f, 0.0f
	};
}

void Cube::render()
{
	VAO->bind();
	text->bind();

	glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0);
}