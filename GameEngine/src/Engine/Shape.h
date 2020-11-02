#ifndef SHAPE_H
#define SHAPE_H
#define EXPORTDLL _declspec(dllexport)

#include "Entity.h"

#include "glm/glm.hpp"

class EXPORTDLL Shape : public Entity
{
public:
	Shape();
	Shape(glm::vec3 pos, glm::vec3 scale, Texture* tex);
	~Shape();

protected:
	glm::vec3 posVertex[4];
	glm::vec3 colorVertex[4];
	glm::vec2 texVertex[4];
};
#endif // !SHAPE_H