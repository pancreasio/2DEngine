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

void Renderer::InitializeShapeRenderBuffers(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int &UVBO, glm::vec2 setScale)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glm::vec3 posVertex[4];
	glm::vec3 colorVertex[4];
	glm::vec2 texVertex[4];

	posVertex[0] = { -1.f * setScale.x / 2, 1.f * setScale.y / 2, 0.0f };
	posVertex[1] = { 1.f * setScale.x / 2, 1.f * setScale.y / 2, 0.0f };
	posVertex[2] = { -1.f * setScale.x / 2, -1.f * setScale.y / 2, 0.0f };
	posVertex[3] = { 1.f * setScale.x / 2, -1.f * setScale.y / 2, 0.0f };

	colorVertex[0] = { 1.f, 1.f, 1.f };
	colorVertex[1] = { 1.f, 1.f, 1.f };
	colorVertex[2] = { 1.f, 1.f, 1.f };
	colorVertex[3] = { 1.f, 1.f, 1.f };

	texVertex[0] = { 0.f, 1.f };
	texVertex[1] = { 1.f,1.f };
	texVertex[2] = { 0.f,0.f };
	texVertex[3] = { 1.f,0.f };


	const GLfloat g_vertex_buffer_data[] =
	{
		posVertex[0].x, posVertex[0].y, posVertex[0].z, colorVertex[0].x, colorVertex[0].y, colorVertex[0].z, /*texVertex[0].x, texVertex[0].y,*/
		posVertex[1].x, posVertex[1].y, posVertex[1].z, colorVertex[1].x, colorVertex[1].y, colorVertex[1].z, /*texVertex[1].x, texVertex[1].y,*/
		posVertex[2].x, posVertex[2].y, posVertex[2].z, colorVertex[2].x, colorVertex[2].y, colorVertex[2].z,/* texVertex[2].x, texVertex[2].y,*/
		posVertex[3].x, posVertex[3].y, posVertex[3].z, colorVertex[3].x, colorVertex[3].y, colorVertex[3].z /*, texVertex[3].x, texVertex[3].y*/
	};

	const GLfloat UV_buffer_data[] =
	{
		texVertex[0].x, texVertex[0].y,
		texVertex[1].x, texVertex[1].y,
		texVertex[2].x, texVertex[2].y,
		texVertex[3].x, texVertex[3].y
	};

	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint elements[] =
	{
		0, 1, 2, 3
	};

	glUseProgram(programID);

	// Create an element array
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	GLuint posAttrib = glGetAttribLocation(programID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLuint colAttrib = glGetAttribLocation(programID, "customColor");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colAttrib);

	glGenBuffers(1, &UVBO);
	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UV_buffer_data), UV_buffer_data, GL_DYNAMIC_DRAW);

	GLuint texAttrib = glGetAttribLocation(programID, "aTexCoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,  2 * sizeof(float), (void*)0);
}

void Renderer::BufferNewUVData(unsigned int &UVBO, float leftU, float rightU, float topV, float bottomV)
{
	const float uvArray[] =
	{
		leftU, topV,
		rightU, topV,
		leftU, bottomV,
		rightU, bottomV
	};

	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvArray), uvArray, GL_DYNAMIC_DRAW);
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
	glBindVertexArray(entityToRender->GetVertexArray());

	glBindTexture(GL_TEXTURE_2D, entityToRender->GetTexturePointer()->GetTexture());

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
}