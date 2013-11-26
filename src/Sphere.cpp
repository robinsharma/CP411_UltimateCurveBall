/*
 * Sphere.cpp
 *
 *  Created on: Nov 15, 2013
 *      Author: Robin
 */

#include "Sphere.hpp"
#include <stdio.h>

Sphere::Sphere() {
	radius = 1.0;

	color[0] = 0.169;
	color[1] = 0.612;
	color[2] = 0.71;
	color[3] = 0.5;
	quad = 0;
	textureID = 0;


	sphere_center_mc[0] = 0;
	sphere_center_mc[1] = 0;
	sphere_center_mc[2] = 0;
	sphere_center_mc[3] = 1.0;

	sphere_center_wc[0] = 0;
	sphere_center_wc[1] = 0;
	sphere_center_wc[2] = 0;
	sphere_center_wc[3] = 1.0;

}

void Sphere::changeColor(GLfloat red, GLfloat green, GLfloat blue) {
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}

void Sphere::draw() {
	this->quad = gluNewQuadric();
	gluQuadricTexture(this->quad, GL_TRUE);
	gluQuadricOrientation(this->quad, GLU_OUTSIDE);
	gluQuadricNormals(this->quad, GLU_SMOOTH);
	sphere_center_wc[0] = sphere_center_mc[0];
	sphere_center_wc[1] = sphere_center_mc[1];
	sphere_center_wc[2] = sphere_center_mc[2];
	sphere_center_wc[3] = 1.0;
	this->MC.multiply_vector(sphere_center_wc);
	printf("(%f, %f, %f) \n",sphere_center_wc[0],sphere_center_wc[1],sphere_center_wc[2]);
	glPushMatrix();
	this->ctm_multiply();
	glScalef(scale_x, scale_y, scale_y);
	glColor3f(color[0], color[1], color[2]);
	//glutWireSphere(1.0, 30, 30);
	gluSphere(this->quad, 1.0, 30, 30);
	glPopMatrix();
	gluDeleteQuadric(this->quad);


}

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

