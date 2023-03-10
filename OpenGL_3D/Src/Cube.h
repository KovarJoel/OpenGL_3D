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
	const std::vector<GLuint> indices = {
		0,   1,  2,      2,  3,  0,     // front
		4,   5,  6,      6,  7,  4,     // right
		8,   9, 10,     10, 11,  8,     // back
		12, 13, 14,     14, 15, 12,     // left
		16, 17, 18,     18, 19, 16,     // top
		20, 21, 22,     22, 23, 20      // bottom
	};
	//std::vector<Texture> textures;
	std::unique_ptr<ShaderProgram> shader = nullptr;
	std::unique_ptr<Texture> texture = nullptr;
	std::unique_ptr<VertexArray> VAO = nullptr;

	glm::mat4 model{}, view{}, projection{};

public:
	//Cube(float size, float red, float green, float blue, float alpha);
	Cube(float size, const std::string& texturePath);
	//Cube(float length, std::vector<char*> texturePaths);
	~Cube() = default;

	void setSize(float length);
	void setModelMatrix(const glm::mat4& model);
	void setMatrix4Uniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
	
	void render() const;
};