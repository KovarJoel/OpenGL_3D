#include "Game.h"

Game::Game(const char* windowTitle, int width, int height)
	:width(width), height(height)
{
	if (!glfwInit())
	{
		std::cout << "ERROR::GLFW::INIT" << std::endl;
		_getch();
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
		_getch();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}

	glEnable(GL_DEPTH_TEST);

	box = new ContainerBox;
}

Game::~Game()
{
	delete box;

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Game::handleEvents()
{
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	box->handleEvents(window);
}

void Game::render()
{
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	box->render();

	glfwSwapBuffers(window);
}

bool Game::isRunning()
{
	return !glfwWindowShouldClose(window);
}