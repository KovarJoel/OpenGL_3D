#include "Game.h"

Game::Game(const char* windowTitle, int width, int height)
	:width(width), height(height)
{
	if (!glfwInit())
	{
		std::cout << "ERROR::GLFW::INIT" << std::endl;
		(void)_getch();
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR::WINDOW::INIT" << std::endl;
		std::cout << glGetError() << std::endl;
		(void)_getch();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);

	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	cubes.reserve(cubePositions.size());
	for (int i = 0; i < cubePositions.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, 0.5f * i * (float)glfwGetTime(), glm::vec3(1.0f, 1.5f, 0.0f));
		cubes.push_back(std::make_unique<Cube>(1.0f, "Src\\Textures\\containerBox.jpg"));
		cubes.at(i)->setMatrix4Uniforms(model, view, projection);
	}
}

Game::~Game()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Game::handleEvents()
{
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Game::render()
{
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < cubePositions.size(); i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, 0.5f * (i + 1) * (float)glfwGetTime(), glm::vec3(1.0f, 1.5f, 0.0f));

		cubes[i]->setModelMatrix(model);
		cubes[i]->render();
	}
	
	glfwSwapBuffers(window);
}

bool Game::isRunning()
{
	return !glfwWindowShouldClose(window);
}