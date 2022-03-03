#ifndef TILE_H
#define TILE_H

#include "Shape.h"

#define EXPORTDLL _declspec(dllexport)

class EXPORTDLL Tile : public Shape
{
public:
	Tile() : Shape(){};
	Tile(glm::vec3 pos, glm::vec3 scale, Texture* tex, float Ucoord, float Vcoord, float tileWidth, float tileHeight);
	bool isSolid = false;
	~Tile();
};

#endif