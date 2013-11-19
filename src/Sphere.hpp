/*
 * Sphere.hpp
 *
 *  Created on: Nov 15, 2013
 *      Author: Robin
 */

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include <windows.h>
#include <GL/glut.h>
#include "Shape.hpp"

class Sphere: public Shape {
protected:

public:
	GLfloat color[3];
	GLfloat radius;
	GLfloat location[1][3];
	GLuint textureID;
	GLUquadric *quad;

	Sphere();
	void draw();
	void drawShape(GLuint texture);

};

#endif /* SPHERE_HPP_ */
