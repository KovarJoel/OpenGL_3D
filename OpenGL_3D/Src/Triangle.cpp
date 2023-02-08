#include "Triangle.h"

Triangle::Triangle()
{
	init();
}

Triangle::Triangle(float* vertices)
{
	updateVertices(vertices);
	init();
}

Triangle::~Triangle()
{
	delete VAO;
	delete shaderProgram;
}

void Triangle::init()
{
	VAO = new VertexArray(vertices, {3, 3});
	shaderProgram = new ShaderProgram("Src\\Shaders\\vertexShader.glsl", "Src\\Shaders\\fragmentShader.glsl");
}

void Triangle::updateVertices(float* vertices)
{
	for (int i = 0; i < 3 * 3; i++)
	{
		this->vertices[i] = vertices[i];
	}
}

void Triangle::updateShaders(const char* vertexPath, const char* fragmentPath)
{
	shaderProgram->update(vertexPath, fragmentPath);
}

void Triangle::render()
{
	shaderProgram->bind();
	VAO->bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	VAO->unbind();
}