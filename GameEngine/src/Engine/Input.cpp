#include "Input.h"

Input::Input(GLFWwindow* window)
{
	currentWindow = window;
}

bool Input::GetKey(int key)
{
	if (glfwGetKey(currentWindow, key) == GLFW_PRESS)
	{
		return true;
	}
	return false;
}

bool Input::GetKeyUp(int key)
{
	if (glfwGetKey(currentWindow, key) == GLFW_RELEASE)
	{
		return true;
	}
	return false;
}