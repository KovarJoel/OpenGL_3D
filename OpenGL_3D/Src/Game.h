#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <conio.h>

#include "Triangle.h"
#include "ContainerBox.h"

class Game
{
private:
	int width = 0, height = 0;

	GLFWwindow* window = nullptr;
	ContainerBox* box = nullptr;

public:
	Game(const char* windowTitle, int width, int height);
	~Game();

	void handleEvents();
	void render();

	bool isRunning();
};