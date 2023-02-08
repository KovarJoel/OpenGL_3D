#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shaders/ShaderProgram.h"
#include "VertexArray.h"

class Triangle
{
private:
	 std::vector<float> vertices = {
		 +0.0f, +0.5f, +0.0f, 0.0f, 0.0f, 1.0f,
		 +0.5f, -0.5f, +0.0f, 1.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f, +0.0f, 0.0f, 1.0f, 0.0f
	 };

	 ShaderProgram* shaderProgram = nullptr;
	 VertexArray* VAO;

	 void init();

public:
	Triangle();
	Triangle(float* vertices);
	~Triangle();

	void updateVertices(float* vertices);
	void updateShaders(const char* vertexPath, const char* fragmentPath);
	void render();
};