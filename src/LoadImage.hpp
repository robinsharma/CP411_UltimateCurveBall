/*
 * LoadImage.hpp
 *
 *  Created on: Nov 16, 2013
 *      Author: Robin
 */

#ifndef LOADIMAGE_HPP_
#define LOADIMAGE_HPP_

#include <windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

class Image {
public:
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
	Image();
	int ImageLoad(char *);

};
#endif /* LOADIMAGE_HPP_ */
