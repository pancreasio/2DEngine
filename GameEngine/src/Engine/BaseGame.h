#ifndef BASEGAME_H
#define BASEGAME_H
#define EXPORTDLL _declspec(dllexport)

#include <list>

#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "CollisionManager.h"
#include "Texture.h"

class Entity;
class Shape;
class Sprite;
class Tilemap;

class EXPORTDLL BaseGame
{
public:
	BaseGame(int screenWidth, int screenHeight);
	~BaseGame();
	int GameLoop();
	Shape* CreateShape(glm::vec3 pos, glm::vec3 setScale, Texture* tex, int drawLayer);
	Sprite* CreateSprite(glm::vec3 pos, glm::vec3 setScale, Texture* tex, int drawLayer);
	void InitializeTilemap(Tilemap* targetTilemap, const char* tileMapPath, const char* tileSetPath, Texture* tilesetTexture, int drawLayer);
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
	Texture* transparentTexture;
};

#endif