/*
 * Pyramid.cpp
 *
 *  Created on: Oct 17, 2013
 *      Author: Robin Sharma
 */


#include "Pyramid.hpp"

Pyramid::Pyramid() {
	vertex[0][0] = -1;vertex[0][1] = -1;vertex[0][2] = -1;
	vertex[1][0] = 1;vertex[1][1] = -1;vertex[1][2] = -1;
	vertex[2][0] = -1;vertex[2][1] = -1;vertex[2][2] = 1;
	vertex[3][0] = 1;vertex[3][1] = -1;vertex[3][2] = 1;
	vertex[4][0] = 0;vertex[4][1] = 1;vertex[4][2] = 0; // top point

	face[0][0] = 0;face[0][1] = 1;face[0][2] = 3; face[0][3] = 2; // base
    face[1][0] = 0;face[1][1] = 1;face[1][2] = 4;
    face[2][0] = 0;face[2][1] = 2;face[2][2] = 4;
    face[3][0] = 1;face[3][1] = 3;face[3][2] = 4;
    face[4][0] = 2;face[4][1] = 3;face[4][2] = 4;

}

//For house
Pyramid::Pyramid(float x) {
	vertex[0][0] = -1;vertex[0][1] = -1;vertex[0][2] = -1;
	vertex[1][0] = 1;vertex[1][1] = -1;vertex[1][2] = -1;
	vertex[2][0] = -1;vertex[2][1] = -1;vertex[2][2] = 1;
	vertex[3][0] = 1;vertex[3][1] = -1;vertex[3][2] = 1;
	vertex[4][0] = 0;vertex[4][1] = x;vertex[4][2] = 0; // top point

	face[0][0] = 0;face[0][1] = 1;face[0][2] = 3; face[0][3] = 2; // base
    face[1][0] = 0;face[1][1] = 1;face[1][2] = 4;
    face[2][0] = 0;face[2][1] = 2;face[2][2] = 4;
    face[3][0] = 1;face[3][1] = 3;face[3][2] = 4;
    face[4][0] = 2;face[4][1] = 3;face[4][2] = 4;

}

void Pyramid::draw_face(int i)
{
    glBegin(GL_LINE_LOOP);
    glVertex3fv(&vertex[face[i][0]][0]);
    glVertex3fv(&vertex[face[i][1]][0]);
    glVertex3fv(&vertex[face[i][2]][0]);
    if( i == 0 ) { //need 4 edges for base! :)
    	glVertex3fv(&vertex[face[i][3]][0]);
    }
    glEnd();
}

void Pyramid::draw()
{
    glPushMatrix();
    this->ctm_multiply();
	glScalef(scale_x, scale_y, scale_z);
    for (int i = 0; i < 4; i++) {
        draw_face(i);
    }
    glPopMatrix();
}
