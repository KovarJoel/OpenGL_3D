#pragma once
#include "Shaders/ShaderProgram.h"
#include "Textures/Texture.h"
#include "VertexArray.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ContainerBox
{
private:
    std::vector<float> vert;
    const std::vector<GLuint> indices = {
        0,   1,  2,      2,  3,  0,     // front
        4,   5,  6,      6,  7,  4,     // right
        8,   9, 10,     10, 11,  8,     // back
        12, 13, 14,     14, 15, 12,     // left
        16, 17, 18,     18, 19, 16,     // top
        20, 21, 22,     22, 23, 20      // bottom
    };

	ShaderProgram* shaderProgram = nullptr;
	Texture* texture1 = nullptr;
	Texture* texture2 = nullptr;
	VertexArray* VAO = nullptr;
	
	glm::mat4 model{}, view{}, projection{};

public:
	ContainerBox();
	~ContainerBox();

	void handleEvents(GLFWwindow* window);
    void setSize(float length);
	void render();	
};

