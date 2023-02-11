#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DeltaTime.h"

class Camera
{
private:
	glm::vec3 position;

	glm::vec3 up, right, front;

	float YAW = 0.0f, PITCH = 0.0f;
	const float maxPitch = 89.9f;
	double oldX = 0, oldY = 0;

public:
	Camera(const glm::vec3& position, const glm::vec3& target);
	~Camera() = default;

	glm::mat4 getViewMatrix() const;
	void handleEvents(GLFWwindow* window);
};

