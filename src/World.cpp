/**
 * 	World.cpp
 *	CP411 Final Project
 *	Gavin Kerr & Robin Sharma
 *	ID: 110142530
 *	Email: shar2530@mylaurier.ca
 *	Date: November 5, 2013
 */

#include "World.hpp"

World::World() {

	list[0] = new Cube(); 	//Player's paddle
	list[1] = new Cube();	//Opponent's paddle
	list[2] = new Cube();	//Left wall
	list[3] = new Cube();	//Top wall
	list[4] = new Cube(); 	//Right wall
	list[5] = new Cube();	//Bottom wall

	ball = new Sphere();

	length = 6;
}

World::~World() {
	int i = 0;
	for(i = 0; i < length; i++) {
		delete list[i];
	}
}

void World::draw_world() {
	int i = 0;
	for(i = 0; i < length; i++) {
		list[i]->draw();
	}
	ball->draw();

}

