#include "ContainerBox.h"

ContainerBox::ContainerBox()
{
	VAO = new VertexArray(sizeof(vertices) / sizeof(vertices[0]), vertices, { 3, 3, 2 }, {0, 1, 2, 2, 3, 0});
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
	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.5, -0.5f, 0.0f));
	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	texture1->bind();
	texture2->bind();
	shaderProgram->use();
	shaderProgram->setFloatUniform("mixValue", { mixValue });
	shaderProgram->setMatrix4Uniform("transform", { transform });
	VAO->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(-0.5f, -0.5f, 0.0f));
	transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -1.0f));
	float scale = 0.5f * sin(glfwGetTime());
	transform = glm::scale(transform, glm::vec3(scale, scale, scale));
	shaderProgram->setMatrix4Uniform("transform", { transform });
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	VAO->unbind();
}

void ContainerBox::handleEvents(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_UP))
		mixValue += 0.0005f;
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		mixValue -= 0.0005f;

	if (mixValue > 1.0f)
		mixValue = 1.0f;
	if (mixValue < 0.0f)
		mixValue = 0.0f;
}