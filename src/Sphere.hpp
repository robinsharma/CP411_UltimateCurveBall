/*
 * Sphere.hpp
 *
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
	GLfloat sphere_center_mc[4];
	GLfloat sphere_center_wc[4];

	Sphere();
	void draw();
	void drawShape(GLuint texture);
	void changeColor(GLfloat, GLfloat, GLfloat);

};

#endif /* SPHERE_HPP_ */
