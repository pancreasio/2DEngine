#ifndef TEXTURE_H
#define TEXTURE_H
#define EXPORTDLL _declspec(dllexport)

#include "GL/glew.h"

class EXPORTDLL Texture
{
private:
	unsigned int texture;
public:
	Texture(const char* path);
	~Texture();
	unsigned int GetTexture();
};
#endif