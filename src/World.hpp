/**
 * 	World.hpp
 *	Date: November 28, 2013
 */

#ifndef CWORLD_HPP
#define CWORLD_HPP

#include "Cube.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include "WireCube.hpp"
#include <iostream>
#include <list>
#include <vector>


class World {

public:

	Cube* list[6];
	Sphere* ball;
	WireCube* tracker;

	Cube leftWall, topWall, rightWall, bottomWall;
	GLint length;

	World();

	~World();

	void draw_world(); // draw all objects in the world
	void reset();
};

#endif
