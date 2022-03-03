#ifndef	TILEMAP_H
#define TILEMAP_H

#include "Shape.h"
#include "Tile.h"
#include "Texture.h"

#include <list>
#include <vector>

#define EXPORTDLL _declspec(dllexport)

class EXPORTDLL Tilemap
{
private:
	int height;
	int width;
	int tileHeight;
	int tileWidth;
	int tilesetHeight;
	int tilesetWidth;
	int tilesetTilecount;
	int tilesetRows;
	int tilesetColums;

	glm::vec3 tilemapScale;
	glm::vec3 tilemapPosition;

	Texture* tileset;

	float zeroXPosition;
	float zeroYPosition;

	std::list<int> solidTiles;

	std::list<Tile*> tileList;
	std::vector<std::vector<Tile*>> tileVector;
	std::list<Tile*> solidTileList;

public:
	Tilemap(glm::vec3 pos, glm::vec3 scale);
	std::list<Tile*> InitializeTilemap(const char* tileMapPath, const char* tileSetPath, Texture* tilesetTexture);
	void SetSolidTiles(std::list<int> solidTileList);
	int GetHeight() { return height; }
	int GetTilesetTileCount() { return tilesetTilecount; }
	int GetTileCount();
	int GetSolidTileCount();
	Tile* GetTile(int tileNumber);
	Tile* GetSolidTile(int tileNumber);
	std::list<Tile*> GetSolidTilesOverlappingShape(Shape targetShape);

protected:
	Tile* InstantiateTile(int xPosition, int yPosition, int tileNumber);
	bool IsSolid(int tileNumber);
	int getXTileCoordinate(int tileNumber);
	int getYTileCoordinate(int tileNumber);
};

#endif
