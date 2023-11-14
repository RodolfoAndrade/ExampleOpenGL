#include "logo.h"

logo::logo(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) :
	texture(image, texType, slot, format, pixelType),
    // square
    vertices{
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.8f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.8f, 0.8f, 0.0f, 1.0f, 0.0f,
        -0.8f, 0.8f, 0.0f, 1.0f, 0.0f,
        -1.0f, 0.8f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    }
{
}

Texture logo::getTexture()
{
	return texture;
}

GLfloat* logo::getVertices()
{
    return vertices;
}

size_t logo::getSizeOf()
{
    return sizeof(vertices);
}
