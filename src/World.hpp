/**
 * 	World.hpp
 *	CP411 Assignment 2
 *	Robin Sharma
 *	ID: 110142530
 *	Email: shar2530@mylaurier.ca
 *	Date: October 18, 2013
 */

#ifndef CWORLD_HPP
#define CWORLD_HPP

#include "Cube.hpp"
#include "Pyramid.hpp"
#include "House.hpp"
#include "Light.hpp"
#include "SolarSystem.hpp"
#include "Bezier.hpp"
#include "wcPt3D.hpp"
//#include "Shape.hpp"
#include <iostream>
#include <list>
#include <vector>


class World {

public:

	Shape* list[3];

	GLint length;

	// std::list<Shape*> ObjectList;
	// std::vector<Shape*>* ObjectVector;

	World();

	~World();

	void draw_world(); // draw all objects in the world

};

#endif
