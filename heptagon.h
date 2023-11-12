#pragma once
#include <GLFW/glfw3.h>
#include <cmath>

class heptagon
{
private:
	// pi
	float pi;
	// 1/7 of 2pi
	float angle;
	// Angles of the vertices
	float angles[8];
	// Vertices of the heptagon
	GLfloat vertices[7*3*6];
public:
	// Constructor for the heptagon
	heptagon();
	GLfloat *getVertices();
	size_t getSizeOf();
	void update();
};

