#ifndef INPUT_H
#define INPUT_H
#define EXPORTDLL _declspec(dllexport)

#include "GLFW/glfw3.h"

class EXPORTDLL Input
{
private:
	GLFWwindow* currentWindow;
public:
	Input(GLFWwindow* window);
	bool GetKey(int key);
	bool GetKeyUp(int key);
};

#endif