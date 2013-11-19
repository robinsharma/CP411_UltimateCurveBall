/*
 * LoadImage.cpp
 *
 *  Created on: Nov 16, 2013
 *      Author: Robin
 */

#include "LoadImage.hpp"

Image::Image() {
	sizeX = 0, sizeY = 0;
	data = "";
}

int Image::ImageLoad(char *filename) {
	FILE *file;
	unsigned long size; // size of the image in bytes.
	unsigned long i; // standard counter.
	unsigned short int planes; // number of planes in image (must be 1)
	unsigned short int bpp; // number of bits per pixel (must be 24)

	char temp; // temporary color storage for bgr-rgb conversion.

	// make sure the file is there.
	if ((file = fopen(filename, "rb")) == NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}

	// seek through the bmp header, up to the width/height:

	fseek(file, 18, SEEK_CUR);

	// read the width

	if ((i = fread(&sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}

	// read the height
	if ((i = fread(&sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}

	size = sizeX * sizeY * 3;

	if ((fread(&planes, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}

	if (planes != 1) {
		printf("Planes from %s is not 1: %u\n", filename, planes);
		return 0;
	}

	// read the bitsperpixel
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);
		return 0;
	}

	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}

	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);

	data = (char *) malloc(size);
	if (data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}

	if ((i = fread(data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (i = 0; i < size; i += 3) { // reverse all of the colors. (bgr -> rgb)
		temp = data[i];
		data[i] = data[i + 2];
		data[i + 2] = temp;
	}
	return 1;
}


