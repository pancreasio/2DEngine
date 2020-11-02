#ifndef	SPRITE_H
#define SPRITE_H

#define EXPORTDLL _declspec(dllexport)

#include "Shape.h"

#include "glm/glm.hpp"

class Animation;

class EXPORTDLL Sprite : public Shape
{
private:
	Animation* animation;
public:
	Sprite(glm::vec3 pos, glm::vec3 scale, Texture* tex) : Shape(pos, scale, tex) {};
	~Sprite();
	void CreateAnimation(float spritesheetWidth, float frameWidth, int maxRows);
	void UpdateCurrentAnimation(float timer);
	void UpdateBuffer();
	void SetCurrentAnimation(int frameCount, int row, float animTime);
};

#endif