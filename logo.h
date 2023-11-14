#pragma once
#include "Texture.h"
class logo
{
private:
	Texture texture;
	GLfloat vertices[6 * 5];
public:
	logo(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	Texture getTexture();
	GLfloat* getVertices();
	size_t getSizeOf();
};

