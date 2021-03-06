/**
 * 	Cube.hpp
 */

#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>

#include "Shape.hpp"
#include "LoadImage.hpp"


class Cube: public Shape {
protected:
	GLfloat r, g, b;
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat cube_face_norm_mc[6][3]; // normal of faces in MC


	GLfloat faceColor[6][3]; // color for each face

	GLfloat cubeWC[8][4]; /* cube vertices in WC, updated after each movement,*/

	GLint faceIndex[6]; // provide drawing ordering  for painter's algorithm
	GLfloat cubeFaceZ[6]; // Z value of faces, used for sorting by painter's algorithm
	GLfloat backFaceTest[6]; // N * (Ref - P0)
	GLfloat cubeShade[6]; // light shading of each face

	GLfloat cube_face_center_mc[6][3]; // in MC


	//void shade();
	void backFace(GLint);
	void getNormal(GLint);
public:
	Cube();
	void draw_face(int);
	void draw_face_texture(int);
	void draw();
	void updateCube();
	void draw_wire();
	void draw_face_wire(int);
	GLfloat cube_face_center_wc[6][4]; // in WC, will be update from the cube_face_center_mc
	GLfloat cube_face_norm_wc[6][4]; // normal of faces in WC in homogenous cordinates.
	GLfloat cube_center_mc[4];
	GLfloat cube_center_wc[4];

	void setColor(GLfloat, GLfloat, GLfloat);

	GLint textureID;
};

#endif
