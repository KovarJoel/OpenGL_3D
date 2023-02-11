#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& target)
	:position(position)
{
	glm::vec3 direction = glm::normalize(target - position);
	
	PITCH = glm::degrees(asin(direction.y));
	YAW = glm::degrees(asin(direction.z / cos(glm::radians(PITCH))));
	
	front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
	front.y = sin(glm::radians(PITCH));
	front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));

	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(position, position + front, up);
	return view;
}

void Camera::handleEvents(GLFWwindow* window)
{
	double xPos, yPos;
	float deltaTime = (float)DeltaTime::get();

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1))
	{
		glfwGetCursorPos(window, &xPos, &yPos);

		double sens = 11.0f;

		YAW += deltaTime * sens * (oldX - xPos);
		PITCH -= deltaTime * sens * (oldY - yPos);

		oldX = xPos;
		oldY = yPos;

		if (PITCH <= -maxPitch)
			PITCH = -maxPitch;
		else if (PITCH >= maxPitch)
			PITCH = maxPitch;
		
		front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
		front.y = sin(glm::radians(PITCH));
		front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));

		right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
		up = glm::normalize(glm::cross(right, front));
	}

	glfwGetCursorPos(window, &oldX, &oldY);

	float speed = 8.0f;
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		position += deltaTime * speed * front;
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		position -= deltaTime * speed * glm::normalize(glm::cross(front, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		position -= deltaTime * speed * front;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		position += deltaTime * speed * glm::normalize(glm::cross(front, up));
	}
}