/**
 * 	Cube.cpp
 *	CP411 Assignment 3
 *	Robin Sharma
 *	ID: 110142530
 *	Email: shar2530@mylaurier.ca
 *	Date: November 4, 2013
 */

#include "Cube.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include <stdio.h>
using namespace std;

extern Camera myCam;

extern Light Spot;
Cube::Cube() {

	cube_face_norm_mc[0][0] = 0.0, cube_face_norm_mc[0][1] = 0.0, cube_face_norm_mc[0][2] =
			-1.0;
	cube_face_norm_mc[1][0] = 1.0, cube_face_norm_mc[1][1] = 0.0, cube_face_norm_mc[1][2] =
			0.0;
	cube_face_norm_mc[2][0] = 0.0, cube_face_norm_mc[2][1] = 0.0, cube_face_norm_mc[2][2] =
			1.0;
	cube_face_norm_mc[3][0] = -1.0, cube_face_norm_mc[3][1] = 0.0, cube_face_norm_mc[3][2] =
			0.0;
	cube_face_norm_mc[4][0] = 0.0, cube_face_norm_mc[4][1] = 1.0, cube_face_norm_mc[4][2] =
			0.0;
	cube_face_norm_mc[5][0] = 0.0, cube_face_norm_mc[5][1] = -1.0, cube_face_norm_mc[5][2] =
			0.0;

	cube_face_norm_wc[0][0] = 0.0, cube_face_norm_wc[0][1] = 0.0, cube_face_norm_wc[0][2] =
			-1.0;
	cube_face_norm_wc[0][3] = 1.0, cube_face_norm_wc[1][0] = 1.0, cube_face_norm_wc[1][1] =
			0.0;
	cube_face_norm_wc[1][2] = 0.0, cube_face_norm_wc[0][3] = 1.0, cube_face_norm_wc[2][0] =
			0.0;
	cube_face_norm_wc[2][1] = 0.0, cube_face_norm_wc[2][2] = 1.0, cube_face_norm_wc[0][3] =
			1.0;
	cube_face_norm_wc[3][0] = -1.0, cube_face_norm_wc[3][1] = 0.0, cube_face_norm_wc[3][2] =
			0.0;
	cube_face_norm_wc[0][3] = 1.0, cube_face_norm_wc[4][0] = 0.0, cube_face_norm_wc[4][1] =
			1.0;
	cube_face_norm_wc[4][2] = 0.0, cube_face_norm_wc[0][3] = 1.0, cube_face_norm_wc[5][0] =
			0.0;
	cube_face_norm_wc[5][1] = -1.0, cube_face_norm_wc[5][2] = 0.0, cube_face_norm_wc[0][3] =
			1.0;

	faceColor[0][0] = 1.0, faceColor[0][1] = 1.0, faceColor[0][2] = 1.0;
	faceColor[1][0] = 1.0, faceColor[1][1] = 1.0, faceColor[1][2] = 1.0;
	faceColor[2][0] = 1.0, faceColor[2][1] = 1.0, faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0, faceColor[3][1] = 1.0, faceColor[3][2] = 1.0;
	faceColor[4][0] = 1.0, faceColor[4][1] = 1.0, faceColor[4][2] = 1.0;
	faceColor[5][0] = 1.0, faceColor[5][1] = 1.0, faceColor[5][2] = 1.0;

	cubeWC[0][0] = -1, cubeWC[0][1] = -1, cubeWC[0][2] = -1, cubeWC[0][3] = 1;
	cubeWC[1][0] = -1, cubeWC[1][1] = 1, cubeWC[1][2] = -1, cubeWC[1][3] = 1;
	cubeWC[2][0] = 1, cubeWC[2][1] = -1, cubeWC[2][2] = -1, cubeWC[2][3] = 1;
	cubeWC[3][0] = 1, cubeWC[3][1] = 1, cubeWC[3][2] = -1, cubeWC[3][3] = 1;
	cubeWC[4][0] = -1, cubeWC[4][1] = -1, cubeWC[4][2] = 1, cubeWC[4][3] = 1;
	cubeWC[5][0] = -1, cubeWC[5][1] = 1, cubeWC[5][2] = 1, cubeWC[5][3] = 1;
	cubeWC[6][0] = 1, cubeWC[6][1] = -1, cubeWC[6][2] = 1, cubeWC[6][3] = 1;
	cubeWC[7][0] = 1, cubeWC[7][1] = 1, cubeWC[7][2] = 1, cubeWC[7][3] = 1;

	faceIndex[0] = 0, faceIndex[1] = 1, faceIndex[2] = 2;
	faceIndex[3] = 3, faceIndex[4] = 4, faceIndex[5] = 5;
	// light shading of each face
	cubeShade[0] = 1, cubeShade[1] = 1, cubeShade[2] = 1;
	cubeShade[3] = 1, cubeShade[4] = 1, cubeShade[5] = 1;

	cube_face_center_mc[0][0] = 0.0, cube_face_center_mc[0][1] = 0.0, cube_face_center_mc[0][2] =
			-1.0;
	cube_face_center_mc[1][0] = 1.0, cube_face_center_mc[1][1] = 0.0, cube_face_center_mc[1][2] =
			0.0;
	cube_face_center_mc[2][0] = 0.0, cube_face_center_mc[2][1] = 0.0, cube_face_center_mc[2][2] =
			1.0;
	cube_face_center_mc[3][0] = -1.0, cube_face_center_mc[3][1] = 0.0, cube_face_center_mc[3][2] =
			0.0;
	cube_face_center_mc[4][0] = 0.0, cube_face_center_mc[4][1] = 1.0, cube_face_center_mc[4][2] =
			0.0;
	cube_face_center_mc[5][0] = 0.0, cube_face_center_mc[5][1] = -1.0, cube_face_center_mc[5][2] =
			0.0;

	cube_face_center_wc[0][0] = 0.0, cube_face_center_wc[0][1] = 0.0, cube_face_center_wc[0][2] =
			-1.0, cube_face_center_wc[0][3] = 1.0;
	cube_face_center_wc[1][0] = 1.0, cube_face_center_wc[1][1] = 0.0, cube_face_center_wc[1][2] =
			0.0, cube_face_center_wc[1][3] = 1.0;
	cube_face_center_wc[2][0] = 0.0, cube_face_center_wc[2][1] = 0.0, cube_face_center_wc[2][2] =
			1.0, cube_face_center_wc[2][3] = 1.0;
	cube_face_center_wc[3][0] = -1.0, cube_face_center_wc[3][1] = 0.0, cube_face_center_wc[3][2] =
			0.0, cube_face_center_wc[3][3] = 1.0;
	cube_face_center_wc[4][0] = 0.0, cube_face_center_wc[4][1] = 1.0, cube_face_center_wc[4][2] =
			0.0, cube_face_center_wc[4][3] = 1.0;
	cube_face_center_wc[5][0] = 0.0, cube_face_center_wc[5][1] = -1.0, cube_face_center_wc[5][2] =
			0.0, cube_face_center_wc[5][3] = 1.0;

	vertex[0][0] = -1, vertex[0][1] = -1, vertex[0][2] = -1;
	vertex[1][0] = -1, vertex[1][1] = 1, vertex[1][2] = -1;
	vertex[2][0] = 1, vertex[2][1] = -1, vertex[2][2] = -1;
	vertex[3][0] = 1, vertex[3][1] = 1, vertex[3][2] = -1;
	vertex[4][0] = -1, vertex[4][1] = -1, vertex[4][2] = 1;
	vertex[5][0] = -1, vertex[5][1] = 1, vertex[5][2] = 1;
	vertex[6][0] = 1, vertex[6][1] = -1, vertex[6][2] = 1;
	vertex[7][0] = 1, vertex[7][1] = 1, vertex[7][2] = 1;

	face[0][0] = 0, face[0][1] = 1, face[0][2] = 3;
	face[0][3] = 2, face[1][0] = 3, face[1][1] = 7;
	face[1][2] = 6, face[1][3] = 2, face[2][0] = 7;
	face[2][1] = 5, face[2][2] = 4, face[2][3] = 6;
	face[3][0] = 4, face[3][1] = 5, face[3][2] = 1;
	face[3][3] = 0, face[4][0] = 5, face[4][1] = 7;
	face[4][2] = 3, face[4][3] = 1, face[5][0] = 6;
	face[5][1] = 4, face[5][2] = 0, face[5][3] = 2;
}

void Cube::draw_face(int i) {
	glBegin(GL_POLYGON);
	glVertex3fv(&vertex[face[i][0]][0]);
	glVertex3fv(&vertex[face[i][1]][0]);
	glVertex3fv(&vertex[face[i][2]][0]);
	glVertex3fv(&vertex[face[i][3]][0]);
	glEnd();
}

void Cube::draw() {
	glPushMatrix();
	this->ctm_multiply(); // update the CTM
	updateCube(); // update the backFaceTest, etc
	glScalef(sx, sy, sz);
	for (int i = 0; i < 6; i++) {
		if (backFaceTest[faceIndex[i]] < 0) {
			glColor3f(faceColor[faceIndex[i]][0] * cubeShade[faceIndex[i]],
					faceColor[faceIndex[i]][1] * cubeShade[faceIndex[i]],
					faceColor[faceIndex[i]][2] * cubeShade[faceIndex[i]]);
			draw_face(faceIndex[i]);
		}
	}
	glPopMatrix();
}

void Cube::updateCube() {\


	//Shading variables
	GLfloat sx, sy, sz, norm, ns, nx, ny, nz;

	// update cube

	//everything places in one loop for efficiency (avoid running multiple loops)
	for (int i = 0; i < 6; i++) {
		cubeWC[i][0] = vertex[i][0];
		cubeWC[i][1] = vertex[i][1];
		cubeWC[i][2] = vertex[i][2];
		cubeWC[i][3] = 1.0;
		this->MC.multiply_vector(cubeWC[i]);

		//update cube face normal vectors
		//getNormal(i);
		cube_face_norm_wc[i][0] = cube_face_norm_mc[i][0];
		cube_face_norm_wc[i][1] = cube_face_norm_mc[i][1];
		cube_face_norm_wc[i][2] = cube_face_norm_mc[i][2];
		cube_face_norm_wc[i][3] = 1.0;
		this->MC.multiply_vector(cube_face_norm_wc[i]);

		cube_face_center_wc[i][0] = cube_face_center_mc[i][0];
		cube_face_center_wc[i][1] = cube_face_center_mc[i][1];
		cube_face_center_wc[i][2] = cube_face_center_mc[i][2];
		cube_face_center_wc[i][3] = 1.0;
		this->MC.multiply_vector(cube_face_center_wc[i]);

		backFace(i);

		sx = Spot.lx - cube_face_center_wc[i][0];
		sy = Spot.ly - cube_face_center_wc[i][1];
		sz = Spot.lz - cube_face_center_wc[i][2];

		nx = cube_face_norm_wc[i][0];
		ny = cube_face_norm_wc[i][1];
		nz = cube_face_norm_wc[i][2];

		norm = sqrt(sx * sx + sy * sy + sz * sz);
		ns = (nx * sx + ny * sy + nz * sz) / norm;

		if (ns > 0) {
			if (Spot.B * Spot.Ka + Spot.P * Spot.Kd * ns <= 1)
				cubeShade[i] = Spot.B * Spot.Ka + Spot.P * Spot.Kd * ns; // shade of the face i
			else
				cubeShade[i] = 1;
		} else
			cubeShade[i] = Spot.B * Spot.Ka;
	}

}

void Cube::backFace(GLint i) {
	backFaceTest[i] = ((myCam.xref - myCam.xeye) * cube_face_norm_wc[i][0])
			+ ((myCam.yref - myCam.yeye) * cube_face_norm_wc[i][1])
			+ ((myCam.zref - myCam.zeye) * cube_face_norm_wc[i][2]);
}

void Cube::getNormal(GLint i) {
	GLfloat p0[3], p1[3], p2[3];
	p0[0] = vertex[face[i][0]][0];
	p0[1] = vertex[face[i][0]][1];
	p0[2] = vertex[face[i][0]][2];

	p1[0] = vertex[face[i][1]][0];
	p1[1] = vertex[face[i][1]][1];
	p1[2] = vertex[face[i][1]][2];

	p2[0] = vertex[face[i][3]][0];
	p2[1] = vertex[face[i][3]][1];
	p2[2] = vertex[face[i][3]][2];
	cube_face_norm_mc[i][0] = ((p1[1] - p0[1]) * (p2[2] - p1[2]))
			- ((p2[1] - p1[1]) * (p1[2] - p0[2]));
	printf("Normal x: %f\n", cube_face_norm_mc[i][0]);

	cube_face_norm_mc[i][1] = ((p1[2] - p0[2]) * (p2[0] - p1[0]))
			- ((p2[2] - p1[2]) * (p1[0] - p0[0]));
	cube_face_norm_mc[i][2] = ((p1[0] - p0[0]) * (p2[1] - p1[1]))
			- ((p2[0] - p1[0]) * (p1[1] - p0[1]));

}
