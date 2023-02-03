#pragma once
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "Shaders/ShaderProgram.h"
#include "Textures/Texture.h"
#include "VertexArray.h"

class Cube
{
private:
	float size = 0.0f;

	std::vector<float> vertices;
	std::vector<GLuint> indices = {
		0, 1, 2,	2, 3, 0,	// front
		1, 5, 6,	6, 2, 1,	// right
		5, 4, 7,	7, 6, 5,	// back
		4, 0, 3,	3, 7, 4,	// left
		0, 1, 5,	5, 4, 0,	// top
		3, 2, 6,	6, 7, 3		// bottom
	};
	//std::vector<Texture> textures;
	Texture* text = nullptr;
	VertexArray* VAO = nullptr;

public:
	//Cube(float size, float red, float green, float blue, float alpha);
	Cube(float size, const char* texture);
	//Cube(float length, std::vector<char*> texturePaths);
	~Cube();

	void setSize(float length);
	
	void render();
};

