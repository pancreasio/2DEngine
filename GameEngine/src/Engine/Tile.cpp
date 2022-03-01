#include "Tile.h"

Tile::Tile(glm::vec3 pos, glm::vec3 scale, Texture* tex, float Ucoord, float Vcoord, float tileWidth, float tileHeight) : Shape(pos, scale, tex)
{

	BufferUVData(Ucoord * tileWidth, (Ucoord + 1) *tileWidth, (Vcoord + 1) * tileHeight, Vcoord * tileHeight);
}