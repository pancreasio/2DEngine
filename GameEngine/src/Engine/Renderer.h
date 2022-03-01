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
#include <map>
class Entity;

class EXPORTDLL Renderer
{
public:
	Renderer(Window* window);
	~Renderer();
	void Render(std::list<Entity*> objectList);// const;
	void RenderLayers();
	void SetBackgroundColor(float r, float g, float b, float a) const; 
	void AddEntityToLayer(Entity* entityToAdd, int targetLayer);
	void InitializeShapeRenderBuffers(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int &UVBO, glm::vec2 setScale);
	void BufferNewUVData(unsigned int &UVBO , float leftU, float rightU, float topV, float bottomV);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
	std::map<int, std::list<Entity*>> layerMap;
	GLuint GetShader();
private:
	void SetShader();
	void RenderEntity(Entity* entityToRender);
	unsigned int uniModel;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	GLuint programID; 
	GLFWwindow* renderWindow;

	std::list<Entity*> baseLayer;
	void SortLayers();
};

#endif // !RENDERER_H