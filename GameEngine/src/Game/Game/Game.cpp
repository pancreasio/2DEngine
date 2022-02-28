#include "Game.h"
#include "Engine/BaseGame.h"
#include "Engine/Texture.h"

#include <iostream>

Game::Game(int width, int height) : BaseGame(width, height)
{

}

Game::~Game()
{
	delete shape;
	delete shape2;
	delete anim;
}

void Game::Init()
{
	Texture bokeTex("../res/BOKEE.png");
	Texture comuTex("../res/texture.png");
	Texture animTex("../res/anim.png");
	Texture terrainTex("../res/terrain sprite.png");

	shape = CreateShape({ 300,0,0 }, { 100,100,0 }, &bokeTex, 3);
	shape2 = CreateShape({ 100.f,0.f,1.f }, { 90,90,0 }, &comuTex,2);

	anim = CreateSprite({ 200,0,0 }, { 36.8f, 20, 0 }, &animTex, 4);
	anim->CreateAnimation(368, 368 / 8, 4);
	anim->SetCurrentAnimation(8, 0, 0.4);
	
	tilemap = new Tilemap({ 0.f,0.f,0.f }, { 3.f,3.f,1.f });
	tilemap->SetSolidTiles({ 3 });
	/*tilemap->InitializeTilemap("../res/terrainTilemap.xml", "../res/terrainTileset.xml", &terrainTex);*/
	InitializeTilemap(tilemap,"../res/terrainTilemap.xml", "../res/terrainTileset.xml", &terrainTex,3);
	safePositionExists = false;
	safePosition = { 0.f,0.f };

	GameLoop();
}

void Game::Update(const float deltaTime)
{
	//scaling

	if (input->GetKey(GLFW_KEY_H))
	{
		anim->Scale({ 1.1f,1.1f,1.1f });
	}

	if (input->GetKey(GLFW_KEY_K))
	{
		anim->Scale({ 0.9f,0.9f,0.9f });
	}

	if (input->GetKey(GLFW_KEY_N))
	{
		shape2->Scale({ 1.1f,1.1f,1.1f });
	}

	if (input->GetKey(GLFW_KEY_M))
	{
		shape2->Scale({ 0.9f,0.9f,0.9f });
	}

	//rotating
	if (input->GetKey(GLFW_KEY_E))
	{
		anim->Rotate(-1.0f, { 0.0f,0.0f,1.f });
		anim->SetCurrentAnimation(8, 2, 2);
	}

	if (input->GetKey(GLFW_KEY_F))
	{
		anim->Rotate(-1.0f, { 0.0f,1.0f,0.f });
		anim->SetCurrentAnimation(8, 2, 2);
	}

	else if (input->GetKey(GLFW_KEY_Q))
	{
		anim->Rotate(1.0f, { 0.0f,0.0f,1.f });
		anim->SetCurrentAnimation(6, 1, 2);
	}

	//translating
	if (input->GetKey(GLFW_KEY_A))
	{
		shape2->Translate(-60.f *shapeMovespeed, { 1.0f,0.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_D))
	{
		shape2->Translate(60.f*shapeMovespeed, { 1.0f,0.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_W))
	{
		shape2->Translate(60.f*shapeMovespeed, { 0.0f,1.0f,0.0f });
	}
	if (input->GetKey(GLFW_KEY_S))
	{
		shape2->Translate(-60.f*shapeMovespeed, { 0.0f,1.0f,0.0f });
	}

	if (input->GetKey(GLFW_KEY_LEFT))
	{
		anim->Translate(-60.f, { 1.0f,0.0f,0.0f });
		anim->SetCurrentAnimation(8, 0, 0.4);
	}

	if (input->GetKey(GLFW_KEY_RIGHT))
	{
		anim->Translate(60.f, { 1.0f,0.0f,0.0f });
		anim->SetCurrentAnimation(8, 0, 0.4);
	}

	if (input->GetKey(GLFW_KEY_UP))
	{
		anim->Translate(60.f, { 0.0f,1.0f,0.0f });
		anim->SetCurrentAnimation(8, 0, 0.4);
	}
	if (input->GetKey(GLFW_KEY_DOWN))
	{
		anim->Translate(-60.f, { 0.0f,1.0f,0.0f });
		anim->SetCurrentAnimation(8, 0, 0.4);
	}

	//collisions

	/*if (collisionManager->CheckCollision(*shape, *shape2)) 
	{
		if(safePositionExists)
		shape2->SetPosition(safePosition);
	}
	else
	{
		safePosition = shape2->GetPosition();
		safePositionExists = true;
	}*/
	
	if(collisionManager->CheckCollision(*shape2, *tilemap))
	{
		if (safePositionExists)
			shape2->SetPosition(safePosition);
	}
	else
	{
		safePosition = shape2->GetPosition();
		safePositionExists = true;
	}
	

	if (input->GetKey(GLFW_KEY_SPACE)) 
	{
		shape2->SetPosition({ 30.f,30.f });
	}

	anim->UpdateCurrentAnimation(deltaTime);
}