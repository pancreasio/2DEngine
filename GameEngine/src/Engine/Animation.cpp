#include "Animation.h"

Animation::Animation(float spritesheetWidth, float frameWidth, int rows)
{
	this->spritesheetWidth = spritesheetWidth;
	this->frameWidth = frameWidth;
	maxRows = rows;
	actualFrame = 0;
	actualRow = 0;
	frameSizeProportion.x = 1 / (spritesheetWidth / frameWidth);
	frameSizeProportion.y = 1 / (float)maxRows;
	frameTime = 0;
	SetFrameCoords();
}

void Animation::UpdateAnimation(float timer)
{
	if (frameTime >= animationTime / framesCount)
	{
		frameTime = timer - animationTime / framesCount;
		actualFrame++;
		if (actualFrame >= framesCount)
			actualFrame = 0;
	}

	SetFrameCoords();

	frameTime += timer;
}

void Animation::SetFrameCoords()
{
	frameCoords[0] = { actualFrame * frameSizeProportion.x, (actualRow + 1) * frameSizeProportion.y }; //top left
	frameCoords[1] = { (actualFrame + 1) * frameSizeProportion.x, (actualRow + 1) * frameSizeProportion.y }; //top right
	frameCoords[2] = { actualFrame * frameSizeProportion.x, actualRow * frameSizeProportion.y }; //bottom left
	frameCoords[3] = { (actualFrame + 1) * frameSizeProportion.x, actualRow * frameSizeProportion.y }; //bottom right
}

glm::vec2 Animation::GetCurrentFrameCoords(int index)
{
	return frameCoords[index];
}

void Animation::SelectAnimationByRow(int frameCount, int row, float animationTime)
{
	framesCount = frameCount;
	this->animationTime = animationTime;
	actualFrame = 0;
	actualRow = row;
	frameTime = 0;
}