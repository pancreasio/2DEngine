#include "Window.h"

#include "GLFW/glfw3.h"


void Window::open(float windowWidth, float windowHeight, const char* title)
{
	width = windowWidth;
	height = windowHeight;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

GLFWwindow* Window::getWindow()
{
	return window;
}

float Window::GetWidth()
{
	return width;
}

float Window::GetHeight()
{
	return height;
}