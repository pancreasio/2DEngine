#include "Tilemap.h"

#include <iostream>
#include <algorithm>

#include "pugixml.hpp"

Tilemap::Tilemap(glm::vec3 pos, glm::vec3 scale)
{
	tilemapPosition = pos;
	tilemapScale = scale;
}

std::list<Tile*> Tilemap::InitializeTilemap(const char* tileMapPath, const char* tileSetPath, Texture* tilesetTexture)
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

	zeroXPosition = tilemapPosition.x * tilemapScale.x - (float)width * tilemapScale.x *  (float)tileWidth / 2.f;
	zeroYPosition = tilemapPosition.y * tilemapScale.y + (float)height * tilemapScale.y * (float)tileHeight / 2.f;

	tileVector.resize(height);
	for (int i = 0; i < height ; i++)
	{
		tileVector[i].resize(width);
	}

	std::list<Tile*> returnList;
	tileCount = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (tilemapData[tileCount] > 48)
			{
				Tile* newTile = InstantiateTile(j, i, tilemapData[tileCount] - 49);
				tileVector[i][j] = newTile;
				returnList.push_back(newTile);
				if (IsSolid(tilemapData[tileCount] - 48))
				{
					newTile->isSolid = true;
				}
				tileCount++;
			}
		}
	}
		return returnList;
}

void Tilemap::SetSolidTiles(std::list<int> solidTileList)
{
	solidTiles = solidTileList;
}

int Tilemap::GetTileCount()
{
	return tileCount;
}


Tile* Tilemap::GetTile(int tileNumber)
{
	int returnY = floor((float)tileNumber / (float)tileHeight);
	int returnX = tileNumber - (returnY * width);

	return tileVector[returnY][returnX];
}

std::list<Tile*> Tilemap::GetSolidTilesOverlappingShape(Shape targetShape)
{
	std::list<Tile*> returnList;
	int minXcoord = floorf((targetShape.GetPosition().x - targetShape.GetScale().x / 2.f - zeroXPosition - tileWidth * tilemapScale.x / 2.f) / (tileWidth*tilemapScale.x) + 1.f);
	int minYcoord = -floorf((targetShape.GetPosition().y + targetShape.GetScale().y / 2.f - zeroYPosition - tileHeight * tilemapScale.y / 2.f) / (tileHeight*tilemapScale.y) + 1.f);

	int maxXcoord = floorf((targetShape.GetPosition().x + targetShape.GetScale().x / 2.f - zeroXPosition - tileWidth * tilemapScale.x / 2.f) / (tileWidth*tilemapScale.x) + 1.f);
	int maxYcoord = -floorf((targetShape.GetPosition().y - targetShape.GetScale().y / 2.f - zeroYPosition - tileHeight * tilemapScale.y / 2.f) / (tileHeight*tilemapScale.y) +1.f);

	//adjusted formula: floor (left shape position - left tilemap position / tile size)
	//std::cout << "min: x=" << minXcoord << "  y=" << minYcoord << "  max: x=" << maxXcoord << "  y=" << maxYcoord << std::endl; //debug log

	if (minXcoord < 0)
		minXcoord = 0;
	if (minYcoord < 0)
		minYcoord = 0;

	if (maxXcoord > (width - 1))
		maxXcoord = width - 1;
	if (maxYcoord > (height - 1))
		maxYcoord = height - 1;

	//std::cout << "min: x=" << minXcoord << "  y=" << minYcoord << "  max: x=" << maxXcoord << "  y=" << maxYcoord << std::endl;

	int checkCounter = 0;
	for (int i = minYcoord; i <= maxYcoord; i++)
	{
		for (int j = minXcoord; j <= maxXcoord; j++)
		{
			//std::cout << "X= " << j << "  y=" << i;
			if (tileVector[i][j]->isSolid)
			{
				returnList.push_back(tileVector[i][j]);
			}
				checkCounter++;
			//std::cout << std::endl;
		}
	}

	std::cout << "tiles checked: " << checkCounter << std::endl;
	return returnList;
}

Tile* Tilemap::InstantiateTile(int xPosition, int yPosition, int tileNumber)
{
	float resultXPosition = zeroXPosition + (float)xPosition * tileWidth * tilemapScale.x;
	float resultYPosition = zeroYPosition - (float)yPosition * tileHeight * tilemapScale.y;
	glm::vec3 resultPosition = { resultXPosition, resultYPosition, 0.f };
	float resultUcoord = getXTileCoordinate(tileNumber);
	float resultVcoord = glm::abs(getYTileCoordinate(tileNumber) - tilesetRows + 1);
	float resultWidth = 1.f / (float)tilesetColums;
	float resultHeight = 1.f / (float)tilesetRows;
	glm::vec3 resultScale = { tileWidth * tilemapScale.x, tileHeight * tilemapScale.y,1.f };

	return new Tile(resultPosition, resultScale, tileset, resultUcoord, resultVcoord, resultWidth, resultHeight);

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
