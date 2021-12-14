#include "Tile.h"

Tile::Tile(glm::vec3 pos, glm::vec3 scale, Texture* tex, bool solid, float Ucoord, float Vcoord, float tileWidth, float tileHeight) : Shape(pos, scale, tex)
{
	const GLfloat g_vertex_buffer_data[] =
	{
		   posVertex[0].x, posVertex[0].y, posVertex[0].z, colorVertex[0].x, colorVertex[0].y, colorVertex[0].z, Ucoord * tileWidth, (Vcoord + 1) * tileHeight,
		   posVertex[1].x, posVertex[1].y, posVertex[1].z, colorVertex[1].x, colorVertex[1].y, colorVertex[1].z, (Ucoord+1) *tileWidth, (Vcoord + 1) * tileHeight,
		   posVertex[2].x, posVertex[2].y, posVertex[2].z, colorVertex[2].x, colorVertex[2].y, colorVertex[2].z, Ucoord * tileWidth, Vcoord * tileHeight,
		   posVertex[3].x, posVertex[3].y, posVertex[3].z, colorVertex[3].x, colorVertex[3].y, colorVertex[3].z, (Ucoord + 1) * tileWidth, Vcoord * tileHeight
	};

	isSolid = solid;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}