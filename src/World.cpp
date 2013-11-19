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
	mySolar = new SolarSystem();
	myBezier = new Bezier();
	solarAnimationOn = false;
	isBez = true;

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
	delete list[0];
	delete mySolar;
	mySolar = NULL;
	delete myBezier;
	myBezier = NULL;
	//delete list[3];
}

void World::draw_world() {
	if (!solarAnimationOn && !isBez) {
		list[0]->draw();
	} else if (solarAnimationOn){
		mySolar->draw_world();
		//list[3]->draw();
	} else if (isBez) {
		myBezier->draw();
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

