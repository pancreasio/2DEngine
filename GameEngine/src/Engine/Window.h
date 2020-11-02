#ifndef WINDOW_H
#define	WINDOW_H
#define EXPORTDLL _declspec(dllexport)

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class EXPORTDLL Window 
{
public:
	void open(float width, float height, const char* title);
	GLFWwindow* getWindow();
	float GetWidth();
	float GetHeight();
private:
	GLFWwindow* window;
	float width;
	float height;
};

#endif // !WINDOW_H
