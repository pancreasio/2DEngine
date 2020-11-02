#include <iostream>
#include "Game/Game.h"

using namespace std;

void main() 
{
	Game* game = new Game(800,600);
	game->Init();
	delete game;
	cin.get();
}