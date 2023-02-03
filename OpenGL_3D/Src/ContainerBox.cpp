#include "ContainerBox.h"

ContainerBox::ContainerBox()
{
	vert.reserve(120);
	setSize(1.0f);

	VAO = new VertexArray(vert.size(), &vert[0], {3, 2}, indices);
	shaderProgram = new ShaderProgram("Src\\Shaders\\vertexShader.glsl", "Src\\Shaders\\fragmentShader.glsl");
	texture1 = new Texture("Src\\Textures\\containerBox.jpg");
	texture2 = new Texture("Src\\Textures\\awesomeFace.png");
	
	shaderProgram->bind();
	texture1->bind();
	shaderProgram->setIntUniform("texture1", { texture1->getHandle() - 1 });
	texture2->bind();
	shaderProgram->setIntUniform("texture2", { texture2->getHandle() - 1});

	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

ContainerBox::~ContainerBox()
{
	delete VAO;
	delete shaderProgram;
	delete texture1;
	delete texture2;
}

void ContainerBox::render()
{
	model = glm::mat4(1.0f);
	model = glm::rotate(model, 2.0f * (float)glfwGetTime(), glm::vec3(1.0f, 1.5f, 0.0f));

	texture1->bind();
	texture2->bind();
	shaderProgram->bind();
	shaderProgram->setMatrix4Uniform("model", model);
	shaderProgram->setMatrix4Uniform("view", view);
	shaderProgram->setMatrix4Uniform("projection", projection);
	VAO->bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 120);
	VAO->unbind();
}

void ContainerBox::handleEvents(GLFWwindow* window)
{

}

void ContainerBox::setSize(float length)
{
	float size = length / 2.0f;
	
	vert = {
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