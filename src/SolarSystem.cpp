/*
 * SolarSystem.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: Robin
 */

#include "SolarSystem.hpp"

SolarSystem::SolarSystem() {
	Sun = new Sphere();
	Earth = new Sphere();
	Moon = new Sphere();
	myImage = new Image();
	texturesLoaded = false;

	Sun->radius = 1;
	Sun->location[0][0] = 0;
	Sun->location[0][1] = 0;
	Sun->location[0][2] = 0;
	Sun->color[0] = 1.0;
	Sun->color[1] = 0.6;
	Sun->color[2] = 0.1;
	Earth->radius = 0.25;
	Earth->location[0][0] = 2;
	Earth->location[0][1] = 0;
	Earth->location[0][2] = 0;
	Earth->color[0] = 0.0;
	Earth->color[1] = 0.0;
	Earth->color[2] = 1.0;
	Moon->radius = 0.1;
	Moon->location[0][0] = 2.4;
	Moon->location[0][1] = 0;
	Moon->location[0][2] = 0;
	Moon->color[0] = 0.5;
	Moon->color[1] = 1.0;
	Moon->color[2] = 0.0;
	Sun->translate(Sun->location[0][0], Sun->location[0][1],
			Sun->location[0][2]);
	Earth->translate(Earth->location[0][0], Earth->location[0][1],
			Earth->location[0][2]);
	Moon->translate(Moon->location[0][0], Moon->location[0][1],
			Moon->location[0][2]);

}

void SolarSystem::reset() {
	delete Sun;
	delete Earth;
	delete Moon;
	Sun = new Sphere();
	Earth = new Sphere();
	Moon = new Sphere();
}

void SolarSystem::draw_world() { /*1: wire, 4: bitmap */
	glPushMatrix();

	if (texturesLoaded == false) { //only need to load up textures once
		char filename[] = "sun.bmp";
		loadbmp(textures, filename, 0);

		char filename1[] = "earth.bmp";
		loadbmp(textures, filename1, 1);

		char filename2[] = "moon.bmp";
		loadbmp(textures, filename2, 2);

		texturesLoaded = true;
	}

	// material setting for the sun
	GLfloat matAmb1[] = { 0.7, 0.53, 0.3, 1.0 }; //ambient
	GLfloat matDif1[] = { 0.76, 0.57, 0.16, 1.0 }; //diffuse
	GLfloat matSpec1[] = { 1.0, 0.15, 0.0, 1.0 }; //specular
	GLfloat matEm1[] = { 0.75, 0.588, 0.0, 1.0 }; //emission
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec1);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm1);
	Sun->drawShape(textures[0]);

	// material setting for the earth
	GLfloat matAmb2[] = { 0.1, 0.1, 0.2, 1.0 };
	GLfloat matDif2[] = { 0.4, 0.74, 0.7, 1.0 };
	GLfloat matSpec2[] = { 1.0, 0.8, 0.7, 1.0 };
	GLfloat matEm2[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec2);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm2);
	Earth->drawShape(textures[1]);

	// material setting for the moon
	GLfloat matAmb3[] = { 0.2, 0.2, 0.25, 1.0 };
	GLfloat matDif3[] = { 0.8, 0.8, 0.95, 1.0 };
	GLfloat matSpec3[] = { 0.3, 0.3, 1.0, 1.0 };
	GLfloat matEm3[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec3);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm3);
	Moon->drawShape(textures[2]);
	glPopMatrix();
}

bool SolarSystem::loadbmp(GLuint textureArray[], char* strFileName, int ID) {
	if (!strFileName)
		return false;
	myImage->ImageLoad(strFileName);
	if (myImage == NULL)
		exit(0);
	glGenTextures(1, &textureArray[ID]);
	glBindTexture(GL_TEXTURE_2D, textureArray[ID]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, myImage->sizeX, myImage->sizeY, 0, GL_RGB,
	GL_UNSIGNED_BYTE, myImage->data);
	return true;
}
