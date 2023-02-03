#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <conio.h>

#include "Triangle.h"
#include "ContainerBox.h"
#include "Cube.h"

class Game
{
private:
	int width = 0, height = 0;

	const std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	GLFWwindow* window = nullptr;
	ShaderProgram* shader = nullptr;
	std::vector<Cube*> cubes;

	glm::mat4 model{ 1.0f }, view{ 1.0f }, projection{ 1.0f };

public:
	Game(const char* windowTitle, int width, int height);
	~Game();

	void handleEvents();
	void render();

	bool isRunning();
};