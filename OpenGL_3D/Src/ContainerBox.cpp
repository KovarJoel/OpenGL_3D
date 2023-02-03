#include "ContainerBox.h"

ContainerBox::ContainerBox()
{
	VAO = new VertexArray(sizeof(vertices) / sizeof(vertices[0]), vertices, { 3, 2 });
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
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	VAO->unbind();
}

void ContainerBox::handleEvents(GLFWwindow* window)
{

}