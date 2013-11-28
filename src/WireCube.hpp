/**
 * 	WireCube.hpp
 */

#ifndef CWIRECUBE_H
#define CWIRECUBE_H

#include <GL/glut.h>

#include "Shape.hpp"

class WireCube: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];

public:
	WireCube();
	void draw_face(int);
	void draw();
};

#endif
