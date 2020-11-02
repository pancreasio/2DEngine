#ifndef BASEGAME_H
#define BASEGAME_H
#define EXPORTDLL _declspec(dllexport)

#include <list>

#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "CollisionManager.h"

class Entity;

class EXPORTDLL BaseGame
{
public:
	BaseGame(int screenWidth, int screenHeight);
	~BaseGame();
	int GameLoop();
	virtual void Update(const float deltaTime) = 0;
	std::list<Entity*> static entityList;
private:
	Window* window;
	Renderer* renderer;
	float deltaTime;
	float lastFrameTime;
protected:
	Input* input;
	CollisionManager* collisionManager;
};

#endif