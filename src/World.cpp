/**
 * 	World.cpp
 *	CP411 Assignment 3
 *	Robin Sharma
 *	ID: 110142530
 *	Email: shar2530@mylaurier.ca
 *	Date: November 5, 2013
 */

#include "World.hpp"

World::World() {
	list[0] = new Cube();
	list[1] = new Cube();
	list[2] = new Sphere();

	length = 3;
	/* object list
	 ObjectList.push_back(list[0]);
	 ObjectList.push_back(list[1]);
	 */

	/* object vector
	 ObjectVector = new std::vector<Shape*>(2);
	 std::vector<Shape*>& ObjectVecotrRef = *ObjectVector;
	 ObjectVectorRef[0] = list[0];
	 ObjectVectorRef[1] = list[1];
	 */
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

	/*
	 for (std::list<Shape*>::const_iterator it = ObjectList.begin(); it!=ObjectList.end(); ++it) {
	 (*it)->draw();
	 } */

	/*
	 std::vector<Shape*>& ObjectVectorRef = *ObjectVector;
	 for (int i = 0; i < 2; i++ ) {
	 ObjectVectorRef[i]->draw();
	 } */

}

