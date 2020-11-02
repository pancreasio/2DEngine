#ifndef RENDERER_H
#define RENDERER_H
#define EXPORTDLL _declspec(dllexport)

#include <list>

#include "Window.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

class Entity;

class EXPORTDLL Renderer
{
public:
	Renderer(Window* window);
	~Renderer();
	void Render(std::list<Entity*> objectList);// const;
	void SetBackgroundColor(float r, float g, float b, float a) const; 
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
	GLuint GetShader();
private:
	void SetShader();
	void RenderEntity(Entity* entityToRender);
	unsigned int uniModel;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	GLuint programID; 
	GLFWwindow* renderWindow;
};

#endif // !RENDERER_H