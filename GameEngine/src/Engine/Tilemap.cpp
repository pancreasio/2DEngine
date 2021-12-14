#include "Tilemap.h"

#include <iostream>
#include <algorithm>

#include "pugixml.hpp"

Tilemap::Tilemap(glm::vec3 pos, glm::vec3 scale, Texture* backgroundTexture) : Shape(pos, scale, backgroundTexture)
{

}

void Tilemap::InitializeTilemap(const char* tileMapPath, const char* tileSetPath, Texture* tilesetTexture)
{
	tileset = tilesetTexture;
	pugi::xml_document tilemapFile;
	pugi::xml_parse_result tilemapResult = tilemapFile.load_file(tileMapPath);
	height = tilemapFile.child("map").attribute("height").as_int();
	width = tilemapFile.child("map").attribute("width").as_int();

	tileHeight = tilemapFile.child("map").attribute("tileheight").as_int();
	tileWidth = tilemapFile.child("map").attribute("tilewidth").as_int();


	pugi::xml_document tilesetFile;
	pugi::xml_parse_result tilesetResult = tilesetFile.load_file(tileSetPath);
	tilesetColums = tilesetFile.child("tileset").attribute("columns").as_int();
	tilesetTilecount = tilesetFile.child("tileset").attribute("tilecount").as_int();
	tilesetRows = tilesetTilecount / tilesetColums;

	std::string tilemapData = tilemapFile.child("map").child("layer").child("data").text().as_string();
	tilemapData.erase(std::remove(tilemapData.begin(), tilemapData.end(), ','), tilemapData.end());
	tilemapData.erase(std::remove(tilemapData.begin(), tilemapData.end(), ' '), tilemapData.end());
	tilemapData.erase(std::remove(tilemapData.begin(), tilemapData.end(), '\n'), tilemapData.end());

	zeroXPosition = GetPosition().x - (float)width * scale.x *  (float)tileWidth / 2.f;
	zeroYPosition = GetPosition().y + (float)height * scale.y * (float)tileHeight / 2.f;

	
	int dataCounter = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (tilemapData[dataCounter] > 48)
				tileList.push_back(InstantiateTile(j, i, tilemapData[dataCounter] - 49));
			
			dataCounter++;
		}
	}
}

void Tilemap::SetSolidTiles(std::list<int> solidTileList)
{
	solidTiles = solidTileList;
}

int Tilemap::GetTileCount()
{
	return tileList.size();
}

Tile* Tilemap::GetTile(int tileNumber)
{
	std::list<Tile*>::iterator listIterator = tileList.begin();

	std::advance(listIterator, tileNumber);

	return *listIterator;
}

Tile* Tilemap::InstantiateTile(int xPosition, int yPosition, int tileNumber)
{
	float resultXPosition = zeroXPosition + (float)xPosition * tileWidth * scale.x;
	float resultYPosition = zeroYPosition - (float)yPosition * tileHeight * scale.y;
	glm::vec3 resultPosition = { resultXPosition, resultYPosition, 0.f };
	float resultUcoord = getXTileCoordinate(tileNumber);
	float resultVcoord = glm::abs(getYTileCoordinate(tileNumber) - tilesetRows + 1);
	float resultWidth = 1.f / (float)tilesetColums;
	float resultHeight = 1.f / (float)tilesetRows;
	glm::vec3 resultScale = { tileWidth * scale.x, tileHeight * scale.y,1.f };



	return new Tile(resultPosition, resultScale, tileset, IsSolid(tileNumber+1), resultUcoord, resultVcoord, resultWidth, resultHeight);

}

bool Tilemap::IsSolid(int tileNumber)
{
	for (std::list<int>::iterator it = solidTiles.begin(); it != solidTiles.end(); ++it)
	{
		if (tileNumber == *it)
			return true;
	}
	return false;
}

int Tilemap::getXTileCoordinate(int tileNumber)
{
	return tileNumber - getYTileCoordinate(tileNumber) * tilesetColums;
}

int Tilemap::getYTileCoordinate(int tileNumber)
{
	return (int)floorf((float)tileNumber / (float)tilesetColums);
}
