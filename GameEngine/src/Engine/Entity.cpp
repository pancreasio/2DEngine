#include "Entity.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "LoadShader.h"
#include "Texture.h"
#include "BaseGame.h"

Entity::Entity()
{
	position = { 0, 0, 0 };
	BaseGame::entityList.push_front(this);

	model = glm::mat4(1.0f);
	model[3].x += position.x;
	model[3].y += position.y;
	model[3].z += position.z;
	//model[3].z += -500.f;

	position = glm::project({ 0,0,0 }, model, renderer->GetProjMatrix(), glm::vec4(0, 0, 800, 600));
}

Renderer* Entity::renderer = nullptr;
unsigned int Entity::programID = NULL;

Entity::Entity(glm::vec3 pos, Texture* tex)
{
	position = pos;
	BaseGame::entityList.push_front(this);
	texture = tex;

	model = glm::mat4(1.0f);
	model[3].x += position.x;
	model[3].y += position.y;
	model[3].z += position.z;
	//model[3].z += -500.f;

	position = glm::project({ 0,0,0 }, model, renderer->GetProjMatrix(), glm::vec4(0, 0, 800, 600));
}

Entity::~Entity() 
{
	
}

void Entity::Rotate(float angle, glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(angle), axis);
}

void Entity::Scale(glm::vec3 scaleValues)
{
	model = glm::scale(model, scaleValues);
	scale *= scaleValues;
}

void Entity::Translate(float value, glm::vec3 axis)
{
	model = glm::translate(model, value * (axis* 0.01f));
	position += value * axis;
}

glm::vec2 Entity::GetPosition() 
{
	glm::vec2 returnPosition;
	returnPosition.x = model[3].x;
	returnPosition.y = model[3].y;
	return returnPosition;
}

glm::vec2 Entity::GetScale() 
{
	return scale;
}

void Entity::SetPosition(glm::vec2 newPosition)
{
	model[3].x = 0.f + newPosition.x;
	model[3].y = 0.f + newPosition.y;
}

GLuint Entity::GetVertexArray()
{
	return vertexArray;
}

GLuint Entity::GetVertexBuffer() 
{
	return vbo;
}
GLuint Entity::GetElementBuffer() 
{
	return ebo;
}
Texture* Entity::GetTexturePointer()
{
	return texture;
}

glm::mat4 Entity::GetModel() 
{
	return model;
}

unsigned int Entity::GetShader() 
{
	return programID;
}