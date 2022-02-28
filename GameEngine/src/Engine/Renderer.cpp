#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "LoadShader.h"

#include "Renderer.h"
#include "Texture.h"
#include "Entity.h"

#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

Renderer::Renderer(Window* window)
{
	renderWindow = window->getWindow();

	viewMatrix = glm::lookAt(
		glm::vec3(0.f, 0.f, 1.5f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);
	programID = NULL;

	//projMatrix = glm::ortho(0.f,800.f,0.f, 600.f, 0.f, 100.f);
	projMatrix = glm::ortho(-window->GetWidth()/2, window->GetWidth() / 2, -window->GetHeight() / 2, window->GetHeight() / 2, 0.f, 100.f);
	//projMatrix = glm::perspective(45.0f, window->GetWidth()/ window->GetHeight(), 0.f, 100.f);
	//projMatrix = glm::perspectiveFov(45.0f, window->GetWidth(), window->GetHeight(), 0.f, 100.f);

	SetShader();
	layerMap.insert({ 0, baseLayer }); 
}

Renderer::~Renderer()
{
	if (programID != NULL) 
	{
		glDeleteProgram(programID);
	}
}

void Renderer::Render(std::list<Entity*> objectList)// const
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/*draw elements*/
	for (std::list<Entity*>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		RenderEntity(*it);
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(renderWindow);
}

void Renderer::RenderLayers()
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/*draw elements*/
	for (auto it = layerMap.begin(); it != layerMap.end(); ++it)
	{
		for(auto itr = (*it).second.begin(); itr!= (*it).second.end(); ++itr)
			RenderEntity(*itr);
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(renderWindow);
}

void Renderer::SetBackgroundColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

void Renderer::AddEntityToLayer(Entity* entityToAdd, int targetLayer)
{
	if (layerMap.find(targetLayer) == layerMap.end()) // true if layer does not exist yet
		layerMap.insert({ targetLayer, {entityToAdd}});
	else
		layerMap[targetLayer].push_back(entityToAdd);
}

glm::mat4 Renderer::GetViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Renderer::GetProjMatrix()
{
	return projMatrix;
}

GLuint Renderer::GetShader() 
{
	return programID;
}

void Renderer::SetShader()
{
	//load shaders
	programID = LoadShaders("../src/Engine/SimpleVertexShader.vertexshader", "../src/Engine/SimpleFragmentShader.fragmentshader");

	//use shader
	glUseProgram(programID);

	GLint uniView = glGetUniformLocation(programID, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	GLint uniProj = glGetUniformLocation(programID, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projMatrix));

	glUniform1i(glGetUniformLocation(programID, "tex"), 0);

	uniModel = glGetUniformLocation(programID, "model");
}

void Renderer::RenderEntity(Entity* entityToRender) 
{
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(entityToRender->GetModel()));
	glUseProgram(programID);
	glBindVertexArray(entityToRender->GetVertexArray());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entityToRender->GetTexturePointer()->GetTexture());

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
}