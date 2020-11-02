#ifndef	ANIMATION_H
#define ANIMATION_H

#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

class EXPORTDLL Animation
{
public:
	Animation(float spritesheetWidth, float frameWidth, int rows);
	glm::vec2 GetCurrentFrameCoords(int index);
	void UpdateAnimation(float timer);
	void SetFrameCoords();
	void SelectAnimationByRow(int frameCount, int row, float animationTime);
	glm::vec2 frameCoords[4];
private:
	float spritesheetWidth;
	float frameWidth;
	int maxRows;
	int actualRow;
	int framesCount;
	int actualFrame;
	float frameTime;
	glm::vec2 frameSizeProportion;
	float animationTime;
};

#endif