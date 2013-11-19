/**
 * 	House.hpp
 *	CP411 Assignment 2
 *	Robin Sharma
 *	ID: 110142530
 *	Email: shar2530@mylaurier.ca
 *	Date: October 18, 2013
 */

#ifndef HOUSE_HPP_
#define HOUSE_HPP_



#include <GL/glut.h>

#include "Cube.hpp"
#include "Pyramid.hpp"

class House: public Shape {
protected:
	Cube* cube;
	Pyramid* pyramid;

public:
	House();
	void draw();
};





#endif /* HOUSE_HPP_ */
