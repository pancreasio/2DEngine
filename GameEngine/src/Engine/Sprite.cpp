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
	const GLfloat g_vertex_buffer_data[] =
	{
		   posVertex[0].x, posVertex[0].y, posVertex[0].z, colorVertex[0].x, colorVertex[0].y, colorVertex[0].z, animation->frameCoords[0].x, animation->frameCoords[0].y,
		   posVertex[1].x, posVertex[1].y, posVertex[1].z, colorVertex[1].x, colorVertex[1].y, colorVertex[1].z, animation->frameCoords[1].x, animation->frameCoords[1].y,
		   posVertex[2].x, posVertex[2].y, posVertex[2].z, colorVertex[2].x, colorVertex[2].y, colorVertex[2].z, animation->frameCoords[2].x, animation->frameCoords[2].y,
		   posVertex[3].x, posVertex[3].y, posVertex[3].z, colorVertex[3].x, colorVertex[3].y, colorVertex[3].z, animation->frameCoords[3].x, animation->frameCoords[3].y
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Sprite::SetCurrentAnimation(int frameCount, int row, float animTime)
{
	animation->SelectAnimationByRow(frameCount, row , animTime);
}