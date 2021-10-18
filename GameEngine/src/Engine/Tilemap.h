#ifndef	TILEMAP_H
#define TILEMAP_H

#include "Shape.h"

#define EXPORTDLL _declspec(dllexport)

class EXPORTDLL Tilemap : public Shape
{
private:
	int height;
	int width;
	int tileHeight;
	int tilewidth;
	
public:
	Tilemap(glm::vec3 pos, glm::vec3 scale, Texture* backgroundTexture, Texture* tilesetTexture);
	void InitializeTilemap(const char* path);
};

#endif
