#include "Cube.h"

Cube::Cube(float length, const std::string& texturePath)
{	
	vertices.reserve(120);
	setSize(length);

	shader = std::make_unique<ShaderProgram>("Src\\Shaders\\vertexShader.glsl", "Src\\Shaders\\fragmentShader.glsl");
	texture = std::make_unique<Texture>(texturePath);
	VAO = std::make_unique<VertexArray>(vertices, std::vector<GLuint>{ 3, 2 }, indices);
}

void Cube::setSize(float length)
{
	size = length / 2.0f;

	vertices = {
		//	x,	   y,	  z,	w,	  h,
		// front
		-size, +size, +size, 0.0f, 1.0f,	// 00 top left
		+size, +size, +size, 1.0f, 1.0f,	// 01 top right
		+size, -size, +size, 1.0f, 0.0f,	// 02 bottom  right
		-size, -size, +size, 0.0f, 0.0f,	// 03 bottom left
		// right
		+size, +size, +size, 0.0f, 1.0f,	// 04 top left
		+size, +size, -size, 1.0f, 1.0f,	// 05 top right
		+size, -size, -size, 1.0f, 0.0f,	// 06 bottom  right
		+size, -size, +size, 0.0f, 0.0f,	// 07 bottom left
		// back
		-size, +size, -size, 0.0f, 1.0f,	// 08 top left
		+size, +size, -size, 1.0f, 1.0f,	// 09 top right
		+size, -size, -size, 1.0f, 0.0f,	// 10 bottom  right
		-size, -size, -size, 0.0f, 0.0f,	// 11 bottom left
		// left
		-size, +size, -size, 0.0f, 1.0f,	// 12 top left
		-size, +size, +size, 1.0f, 1.0f,	// 13 top right
		-size, -size, +size, 1.0f, 0.0f,	// 14 bottom  right
		-size, -size, -size, 0.0f, 0.0f,	// 15 bottom left
		// top
		-size, +size, -size, 0.0f, 1.0f,	// 16 back left
		+size, +size, -size, 1.0f, 1.0f,	// 17 back right
		+size, +size, +size, 1.0f, 0.0f,	// 18 front right
		-size, +size, +size, 0.0f, 0.0f,	// 19 front left
		// bottom
		-size, -size, -size, 0.0f, 1.0f,	// 20 back left
		+size, -size, -size, 1.0f, 1.0f,	// 21 back right
		+size, -size, +size, 1.0f, 0.0f,	// 22 front right
		-size, -size, +size, 0.0f, 0.0f,	// 23 front left
	};
}

void Cube::setModelMatrix(const glm::mat4& model)
{
	this->model = model;
	shader->bind();
	shader->setMatrix4Uniform("model", model);
}

void Cube::setMatrix4Uniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
	this->model = model;
	this->view = view;
	this->projection = projection;

	shader->bind();
	shader->setMatrix4Uniform("model", model);
	shader->setMatrix4Uniform("view", view);
	shader->setMatrix4Uniform("projection", projection);
}

void Cube::render() const
{
	shader->bind();
	texture->bind();
	VAO->bind();

	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

	VAO->unbind();
}