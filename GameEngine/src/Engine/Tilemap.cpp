#include "Tilemap.h"

#include "pugixml.hpp"

Tilemap::Tilemap(glm::vec3 pos, glm::vec3 scale, Texture* backgroundTexture) : Shape(pos, scale, backgroundTexture)
{
	
}

void Tilemap::InitializeTilemap(const char* tileMapPath, const char* tileSetPath, Texture* tilesetTexture, Texture* noTileTexture)
{
	tileset = tilesetTexture;
	noTile = noTileTexture;
	pugi::xml_document tilemapFile;
	pugi::xml_parse_result tilemapResult = tilemapFile.load_file(tileMapPath);
	height = tilemapFile.child("map").attribute("height").as_int();
	width = tilemapFile.child("map").attribute("width").as_int();

	tileHeight = tilemapFile.child("map").attribute("tileheight").as_int();
	tileWidth = tilemapFile.child("map").attribute("tileWidth").as_int();

	pugi::xml_document tilesetFile;
	pugi::xml_parse_result tilesetResult = tilesetFile.load_file(tileSetPath);
	tilesetWidth = tilesetFile.child("tileset").attribute("columns").as_int();
	tilesetTilecount = tilesetFile.child("tileset").attribute("tilecount").as_int();
	tilesetHeight = tilesetTilecount / tilesetWidth;

	zeroXPosition = position.x - (float)width * (float)tileWidth / 2.f + (float)tileWidth/2.f;
	zeroYPosition = position.y + (float)height * (float)tileHeight / 2.f - (float)tileHeight/2.f;
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			tileList.push_back(InstantiateTile(i, j, 4));
		}
	}
}

void Tilemap::SetSolidTiles(std::list<int> solidTileList)
{
	solidTiles = solidTileList;
}

Tile* Tilemap::InstantiateTile(int xPosition, int yPosition, int tileNumber)
{
	float resultXPosition = zeroXPosition + (float)xPosition * (float)tileWidth;
	float resultYPosition = zeroYPosition - (float)yPosition * (float)tileHeight;
	float resultUcoord = (float)getXTileCoordinate(tileNumber) * (float)tileWidth / (float)tilesetWidth * (float)tileWidth;
	float resultVcoord = (float)getYTileCoordinate(tileNumber) * (float)tileHeight / (float)tilesetHeight * (float)tileHeight;
	
	return new Tile({resultXPosition, resultYPosition,0.f},scale,tileset, IsSolid(tileNumber), resultUcoord, resultVcoord, (float)tileWidth, (float)tileHeight);
}

bool Tilemap::IsSolid(int tileNumber)
{
	for(std::list<int>::iterator it = solidTiles.begin(); it!= solidTiles.end(); ++it)
	{
		if (tileNumber == *it)
			return true;
	}
	return false;
}

int Tilemap::getXTileCoordinate(int tileNumber)
{
	return tileNumber - getYTileCoordinate(tileNumber) * tilesetWidth;
}

int Tilemap::getYTileCoordinate(int tileNumber)
{
	return (int) floorf((float)tileNumber / (float)tilesetWidth);
}
