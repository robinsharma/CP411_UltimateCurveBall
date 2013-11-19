/*
 * SolarSystem.hpp
 *
 *  Created on: Nov 5, 2013
 *      Author: Robin
 */

#ifndef SOLARSYSTEM_HPP_
#define SOLARSYSTEM_HPP_

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "LoadImage.hpp"

#include <GL/glut.h>
#include "glaux.h" // for reading bmp texture

#include "Sphere.hpp"

class SolarSystem  {
protected:

public:
	Sphere* Sun;
	Sphere* Earth;
	Sphere* Moon;
	GLuint textures[3];
	Image* myImage;
	bool texturesLoaded;

	SolarSystem();
	void draw_world();
	void set_color(GLfloat, GLfloat, GLfloat);
	void reset();
	bool loadbmp(UINT textureArray[], LPSTR strFileName, int ID);

};

#endif /* SOLARSYSTEM_HPP_ */
