#ifndef GAME_H
#define GAME_H

#include "Engine/BaseGame.h"
#include "Engine/Shape.h"
#include "Engine/Sprite.h"
#include "Engine/Tilemap.h"

class Game : public BaseGame
{
public:
	Game(int width, int height);
	~Game();
	void Init();
	void Update(const float deltaTime);
private:
	Shape* shape;
	Shape* shape2;
	Sprite* anim;
	Tilemap* tilemap;
	glm::vec2 safePosition;
	bool safePositionExists;
	float shapeMovespeed = 30000.f;
	float shapeScaleSpeed = 0.01f;
};

#endif