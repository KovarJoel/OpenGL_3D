#include "ContainerBox.h"

ContainerBox::ContainerBox()
{
	vert.reserve(40);
	setSize(1.0f);

	VAO = new VertexArray(vert.size(), &vert[0], {3, 2}, indices);
	shaderProgram = new ShaderProgram("Src\\Shaders\\vertexShader.glsl", "Src\\Shaders\\fragmentShader.glsl");
	texture1 = new Texture("Src\\Textures\\containerBox.jpg");
	texture2 = new Texture("Src\\Textures\\awesomeFace.png");
	
	shaderProgram->use();
	texture1->bind();
	shaderProgram->setIntUniform("texture1", { texture1->getHandle() - 1 });
	texture2->bind();
	shaderProgram->setIntUniform("texture2", { texture2->getHandle() - 1});
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
	model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	texture1->bind();
	texture2->bind();
	shaderProgram->use();
	shaderProgram->setMatrix4Uniform("model", { model });
	shaderProgram->setMatrix4Uniform("view", { view });
	shaderProgram->setMatrix4Uniform("projection", { projection });
	VAO->bind();
	glDrawElements(GL_TRIANGLES, vert.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	VAO->unbind();
}

void ContainerBox::handleEvents(GLFWwindow* window)
{

}

void ContainerBox::setSize(float length)
{
	float size = length / 2.0f;

	vert = {
		-size, +size, +size, 0.0f, 1.0f,	// 0
		+size, +size, +size, 1.0f, 1.0f,	// 1
		+size, -size, +size, 1.0f, 0.0f,	// 2
		-size, -size, +size, 0.0f, 0.0f,	// 3
											// 
		-size, +size, -size, 0.0f, 1.0f,	// 4
		+size, +size, -size, 1.0f, 1.0f,	// 5
		+size, -size, -size, 1.0f, 0.0f,	// 6
		-size, -size, -size, 0.0f, 0.0f		// 7
	};
}