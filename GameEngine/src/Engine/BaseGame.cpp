#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BaseGame.h"
#include "LoadShader.h"
#include <iostream>

#include "Shape.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Entity.h"
#include "CollisionManager.h"

#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

list<Entity*> BaseGame::entityList;

BaseGame::BaseGame(int screenWidth, int screenHeight)
{
	/* Initialize the library */
	if (!glfwInit())
		glfwTerminate();
	window = new Window();
	entityList.clear();
	window->open(screenWidth, screenHeight, "window");
	collisionManager = new CollisionManager();
	input = new Input(window->getWindow());
	glewExperimental = GL_TRUE;
	glewInit();
	renderer = new Renderer(window);
	Entity::renderer = renderer;
	Entity::programID = renderer->GetShader();
	lastFrameTime = 0.f;
}

BaseGame::~BaseGame()
{
	delete window;
	delete renderer;
}

int BaseGame::GameLoop()
{
	GLFWwindow* currentWindow = window->getWindow();

	while (!glfwWindowShouldClose(currentWindow))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		Update(deltaTime);
		//input processing
		if (input->GetKey(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(currentWindow, GL_TRUE);

		//use renderer		
		renderer->SetBackgroundColor(0.1f, 0.1f, 0.1f, 0.0f);
		renderer->Render(entityList);

		/* Poll for and process events */
		glfwPollEvents();
	}
	delete input;
	glfwTerminate();
	return 0;
}
