#ifndef TILE_H
#define TILE_H

#include "Shape.h"

#define EXPORTDLL _declspec(dllexport)

class EXPORTDLL Tile : public Shape
{
	Tile(glm::vec3 pos, glm::vec3 scale, Texture* tex, bool solid, float Ucoord, float Vcoord, float tileWidth, float tileHeight);
	~Tile();

public:
	bool isSolid;
};

#endif