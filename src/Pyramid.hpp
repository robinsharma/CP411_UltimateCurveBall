/*
 * Pyramid.hpp
 *
 *  Created on: Oct 17, 2013
 *      Author: Robin Sharma
 */

#ifndef PYRAMID_HPP_
#define PYRAMID_HPP_

#include <GL/glut.h>

#include "Shape.hpp"

class Pyramid: public Shape {
protected:
	GLfloat vertex[5][3];
	GLint face[5][4];

public:
	Pyramid();
	Pyramid(float);
	void draw_face(int);
	void draw();
};

#endif /* PYRAMID_HPP_ */
