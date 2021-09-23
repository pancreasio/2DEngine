#ifndef	TILEMAP_H
#define TILEMAP_H

#include "Shape.h"

#define EXPORTDLL _declspec(dllexport)

class EXPORTDLL Tilemap
{
	Tilemap(glm::vec3 pos, glm::vec3 scale, Texture* tex, float tilemapHeight, float tilemapWidth, float tileWidth , int tilemapRows, int tilemapColumns);
};

#endif
