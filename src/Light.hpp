/*
 * Light.hpp
 *
 *  Created on: Oct 24, 2013
 *      Author: Robin
 */

#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <GL/glut.h>
#include "Matrix.hpp"

class Light {
public:
	Light();
	//light and shading
	GLfloat P, B, Ka, Kd;

	// point light position variable
	GLfloat lx, ly, lz;

	void on();
	void off();
	void pointOn();
	void pointOff();
	void resetPosition();
	void resetIllumination();
	void resetAll();
	void draw();
	void rotateWC(GLfloat, GLfloat, GLfloat, GLfloat);
	bool getOn();
protected:
	bool showPoint;
	bool isOn;
};

#endif /* LIGHT_HPP_ */
