/**
 * 	House.cpp
 *	CP411 Assignment 2
 *	Robin Sharma
 *	ID: 110142530
 *	Email: shar2530@mylaurier.ca
 *	Date: October 18, 2013
 */

#include "House.hpp"

House::House() {
	cube = new Cube();
	pyramid = new Pyramid(0.5);
	pyramid->translate(0, 2, 0);
}

void House::draw() {
	glPushMatrix();
	this->ctm_multiply();
	glScalef(sx, sy, sz);
	cube->draw();
	pyramid->draw();
	glPopMatrix();
}

