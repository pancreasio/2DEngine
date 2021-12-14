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
	Texture padarosTex("../res/padaros.png");

	shape = new Shape({ 300,0,0 }, {100,100,0}, &bokeTex);
	shape2 = new Shape({ 100.f,0.f,1.f }, {90,90,0 }, &comuTex);
	anim = new Sprite({ 200,0,0 }, { 36.8f, 20, 0 }, &animTex);
	anim->CreateAnimation(368, 368 / 8, 4);
	anim->SetCurrentAnimation(8, 0, 2);
	
	tilemap = new Tilemap({ 0,0,0 }, { 0.7f,0.7f,0 },transparentTexture);
	tilemap->SetSolidTiles({ 1,5,7 });
	tilemap->InitializeTilemap("../res/PadarosTilemap.xml", "../res/PadarosTileset.xml", &padarosTex);
	safePositionExists = false;
	safePosition = { 0.f,0.f };

	GameLoop();
}

void Game::Update(const float deltaTime)
{
	//scaling
	anim->UpdateCurrentAnimation(deltaTime);

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
		anim->SetCurrentAnimation(8, 0, 2);
	}

	if (input->GetKey(GLFW_KEY_RIGHT))
	{
		anim->Translate(60.f, { 1.0f,0.0f,0.0f });
		anim->SetCurrentAnimation(8, 0, 2);
	}

	if (input->GetKey(GLFW_KEY_UP))
	{
		anim->Translate(60.f, { 0.0f,1.0f,0.0f });
		anim->SetCurrentAnimation(8, 0, 2);
	}
	if (input->GetKey(GLFW_KEY_DOWN))
	{
		anim->Translate(-60.f, { 0.0f,1.0f,0.0f });
		anim->SetCurrentAnimation(8, 0, 2);
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
}