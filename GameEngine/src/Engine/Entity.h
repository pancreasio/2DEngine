#ifndef ENTITY_H
#define ENTITY_H
#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

#include "Renderer.h"

class Texture;

class EXPORTDLL Entity
{
public:
	static Renderer* renderer;
	static unsigned int programID;
	Entity();
	Entity(glm::vec3 pos, Texture* tex);
	~Entity();

	//transformations
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);
	glm::vec2 GetPosition();
	glm::vec2 GetScale();
	void SetPosition(glm::vec2 newPosition);

	//Getters for buffers and pointers
	unsigned int GetVertexArray();
	unsigned int GetVertexBuffer();
	unsigned int GetElementBuffer();
	Texture* GetTexturePointer();
	glm::mat4 GetModel();
	unsigned int GetShader();

protected:
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat4 model;
	unsigned int uniModel;
	unsigned int ebo;
	unsigned int vbo;
	unsigned int vertexArray;
	Texture* texture;
};
#endif