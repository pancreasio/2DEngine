#include "Sprite.h"

#include "Animation.h"

Sprite::~Sprite() 
{
	if (animation != nullptr)
		delete animation;
}

void Sprite::CreateAnimation(float spritesheetWidth, float frameWidth, int maxRows)
{
	if (animation != nullptr)
		delete animation;
	animation = new Animation(spritesheetWidth, frameWidth, maxRows);
	UpdateBuffer();
}

void Sprite::UpdateCurrentAnimation(float timer)
{
	animation->UpdateAnimation(timer);

	UpdateBuffer();
}

void Sprite::UpdateBuffer()
{
	BufferUVData(animation->frameCoords[0].x, animation->frameCoords[1].x, animation->frameCoords[0].y, animation->frameCoords[2].y);
}

void Sprite::SetCurrentAnimation(int frameCount, int row, float animTime)
{
	animation->SelectAnimationByRow(frameCount, row , animTime);
}