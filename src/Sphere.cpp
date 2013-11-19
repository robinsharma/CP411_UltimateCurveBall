/*
 * Sphere.cpp
 *
 *  Created on: Nov 15, 2013
 *      Author: Robin
 */


#include "Sphere.hpp"


Sphere::Sphere() {
	radius = 1.0;
	color[0] = 1;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0.5;
	quad = 0;
	textureID = 0;
}

void Sphere::draw() {}

void Sphere::drawShape(GLuint texture) {
	this->quad = gluNewQuadric();
	gluQuadricTexture(this->quad, GL_TRUE);
	gluQuadricOrientation(this->quad, GLU_OUTSIDE);
	gluQuadricNormals(this->quad, GLU_SMOOTH);
	glPushMatrix();
	this->ctm_multiply();
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	gluSphere(this->quad, radius, 50, 50);

	//glColor4f(color[0], color[1], color[2], color[3]);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(this->quad);
}




