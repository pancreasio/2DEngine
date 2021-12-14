#ifndef	TILEMAP_H
#define TILEMAP_H

#include "Shape.h"
#include "Tile.h"
#include "Texture.h"

#define MAXTILENUMBER 100

#define EXPORTDLL _declspec(dllexport)

class EXPORTDLL Tilemap : public Shape
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

	Texture* noTile;
	Texture* tileset;

	float zeroXPosition;
	float zeroYPosition;
	
	std::list<int> solidTiles;
	
	std::list<Tile*> tileList;
	
public:
	Tilemap(glm::vec3 pos, glm::vec3 scale, Texture* backgroundTexture);
	void InitializeTilemap(const char* tileMapPath, const char* tileSetPath, Texture* tilesetTexture);
	void SetSolidTiles(std::list<int> solidTileList);
	int GetHeight() { return height; }
	int GetTilesetTileCount() { return tilesetTilecount; }
	int GetTileCount();
	Tile* GetTile(int tileNumber);

protected:
	Tile* InstantiateTile(int xPosition, int yPosition, int tileNumber);
	bool IsSolid(int tileNumber);
	int getXTileCoordinate(int tileNumber);
	int getYTileCoordinate(int tileNumber);
};

#endif
