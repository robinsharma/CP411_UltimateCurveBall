/**
 * 	a4.cpp
 *	CP411 Final Project
 *	Robin Sharma & Gavin Kerr
 *	ID: 110142530
 *	Email: shar2530@mylaurier.ca
 *	Date: November 5, 2013
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "Angel.h"

#include <GL/glut.h>

#include "World.hpp"
#include "Camera.hpp"

void mouseMotion(GLint, GLint);
bool loadbmp(UINT textureArray[], LPSTR strFileName, int ID);

GLint winWidth = 800, winHeight = 800;
/*  Set coordinate limits for the clipping window:  */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

/*  Set positions for near and far clipping planes:  */
GLfloat red = 1.0, green = 1.0, blue = 1.0;  //color
GLint moving = 0, start = 0, xBegin = 0, yBegin = 0, coordinate = 1, type = 1,
		selected = 0, game_start = 0;

//Declare a world containing all objects to draw.
World myWorld;
Light Spot;
Camera myCam;

//Lighting substitute lx, ly, lz
GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };
GLfloat positionSolar[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat ambient[] = { 0.1, 0.1, 0.3, 1.0 };
GLfloat diffuse[] = { 0.6, 0.6, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

//Material
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 1, 1, 1, 1 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1, 1, 1, 1 };

GLuint programObject;

GLuint textures[6];
Image* myImage;
bool texturesLoaded;

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(myCam.vangle, 1.0, myCam.dnear, myCam.dfar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(myCam.xeye, myCam.yeye, myCam.zeye, myCam.xref, myCam.yref,
			myCam.zref, myCam.Vx, myCam.Vy, myCam.Vz);
	/* Axis
	 glLineWidth(3);

	 glBegin(GL_LINES);
	 //x-axis
	 glColor3f(1.0, 1.0, 1.0);
	 glVertex3f(2, 0, 0);
	 glVertex3f(0, 0, 0);
	 //y-axis
	 glColor3f(0.0, 1.0, 0.0);
	 glVertex3f(0, 2, 0);
	 glVertex3f(0, 0, 0);
	 //z-axis
	 glColor3f(1.0, 0.0, 0.0);
	 glVertex3f(0, 0, 2);
	 glVertex3f(0, 0, 0);
	 glEnd();
	 glLineWidth(1);*/
	Spot.on();
	if (Spot.getOn()) {
		glEnable(GL_DEPTH_TEST); // enable OpenGL depth buffer algorithm for hidden surface removal
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable( GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHT0);
		glCullFace(GL_BACK);
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

		position[0] = Spot.lx;
		position[1] = Spot.ly;
		position[2] = Spot.lz;

		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	} else {
		glDisable(GL_LIGHTING);
	}

	if (!texturesLoaded) {
		myImage = new Image();

		char filename[] = "earth.bmp";
		loadbmp(textures, filename, 0);

		char filename1[] = "moon.bmp";
		loadbmp(textures, filename1, 1);

		char filename2[] = "sun.bmp";
		loadbmp(textures, filename2, 2);

		char filename3[] = "Wolfsmall.bmp";
		loadbmp(textures, filename3, 3);

		char filename4[] = "Untitled1.bmp";
		loadbmp(textures, filename4, 4);

		myWorld.list[2]->textureID = 0; //left wall
		myWorld.list[3]->textureID = 1; //top wall
		myWorld.list[4]->textureID = 2; //right wall
		myWorld.list[5]->textureID = 3; //bottom wall
		myWorld.list[0]->textureID = 4; //player paddle

		texturesLoaded = true; //only need to load up textures once
	}
	myWorld.draw_world(); // draw all objects in the world
	Spot.draw();

	glFlush();
	glutSwapBuffers();
}

bool loadbmp(GLuint textureArray[], char* strFileName, int ID) {
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

/*-----DISPLAY FUNCTION END----------------------------------------*/

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseAction(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		moving = 1;
		xBegin = x;
		yBegin = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		//moving = 0;
	}
	glutPostRedisplay();

}

void mouseMotion(GLint x, GLint y) {
	//GLfloat rx, ry, rz theta,
	GLfloat thetaX, thetaY;
	if (moving == 1) {
		if (game_start == 1) {
			thetaX = (x - xBegin); //> 0) ? 1 : -1;
			thetaY = (yBegin - y); //> 0) ? 1 : -1;
			myWorld.list[0]->translate(thetaX * 0.003, 0, 0);
			myWorld.list[0]->translate(0, thetaY * 0.003, 0);
			xBegin = x;
			yBegin = y;
			/*
			 } else if (game_start == 0) {
			 theta = (xBegin - x > 0) ? 1 : -1;
			 if (coordinate == 1 && type == 1) { // mc rotate x
			 rx = myWorld.list[selected]->getMC().mat[0][0];
			 ry = myWorld.list[selected]->getMC().mat[1][0];
			 rz = myWorld.list[selected]->getMC().mat[2][0];
			 myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 0.5);
			 } else if (coordinate == 1 && type == 2) { // mc rotate y
			 rx = myWorld.list[selected]->getMC().mat[0][1];
			 ry = myWorld.list[selected]->getMC().mat[1][1];
			 rz = myWorld.list[selected]->getMC().mat[2][1];
			 myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 0.5);
			 } else if (coordinate == 1 && type == 3) { // mc rotate z
			 rx = myWorld.list[selected]->getMC().mat[0][2];
			 ry = myWorld.list[selected]->getMC().mat[1][2];
			 rz = myWorld.list[selected]->getMC().mat[2][2];
			 myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 0.5);
			 } else if (coordinate == 1 && type == 4) { // mc scale
			 myWorld.list[selected]->scaleX(theta * 0.02);
			 } else if (coordinate == 1 && type == 5) { // mc scale
			 myWorld.list[selected]->scaleY(theta * 0.02);
			 } else if (coordinate == 1 && type == 6) { // mc scale
			 myWorld.list[selected]->scaleZ(theta * 0.02);
			 } else if (coordinate == 1 && type == 7) { // mc scale
			 myWorld.list[selected]->scale_change(theta * 0.02);
			 } else if (coordinate == 2 && type == 1) { // wc rotate x
			 rx = 1;
			 ry = 0;
			 rz = 0;
			 myWorld.list[selected]->rotate_origin(rx, ry, rz, theta * 0.5);
			 } else if (coordinate == 2 && type == 2) { // wc rotate y
			 rx = 0;
			 ry = 1;
			 rz = 0;
			 myWorld.list[selected]->rotate_origin(rx, ry, rz, theta * 0.5);
			 } else if (coordinate == 2 && type == 3) { //wc rotate z
			 rx = 0;
			 ry = 0;
			 rz = 1;
			 myWorld.list[selected]->rotate_origin(rx, ry, rz, theta * 0.5);
			 } else if (coordinate == 2 && type == 4) { //wc translate x
			 //myWorld.list[selected]->translate(theta * 0.02, 0, 0);
			 getPos(x, y);
			 //myWorld.list[selected]->translate((float) posX, 0, 0);
			 } else if (coordinate == 2 && type == 5) { //wc translate y
			 myWorld.list[selected]->translate(0, theta * 0.02, 0);
			 } else if (coordinate == 2 && type == 6) { //wc translate z
			 myWorld.list[selected]->translate(0, 0, theta * 0.02);
			 } else if (coordinate == 3 && type == 1) { //VC Rotate x
			 rx = 1;
			 ry = 0;
			 rz = 0;
			 myCam.rotate_view(rx, ry, rz, theta);
			 } else if (coordinate == 3 && type == 2) { //VC Rotate y
			 rx = 0;
			 ry = 1;
			 rz = 0;
			 myCam.rotate_view(rx, ry, rz, theta);
			 } else if (coordinate == 3 && type == 3) { //VC Rotate z
			 rx = 0;
			 ry = 0;
			 rz = 1;
			 myCam.rotate_view(rx, ry, rz, theta);
			 } else if (coordinate == 3 && type == 4) { //VC Translate x
			 myCam.xeye += 0.1 * theta;
			 } else if (coordinate == 3 && type == 5) { //VC Translate y
			 myCam.yeye += 0.1 * theta;
			 } else if (coordinate == 3 && type == 6) { //VC Translate z
			 myCam.zeye += 0.1 * theta;
			 } else if (coordinate == 3 && type == 7) { //VC Clipping Near
			 theta = (xBegin - x < 0) ? 1 : -1;
			 myCam.dnear += 0.1 * theta;
			 } else if (coordinate == 3 && type == 8) { //VC Clipping Far
			 myCam.dfar += 0.1 * theta;
			 } else if (coordinate == 3 && type == 9) { //Angle
			 myCam.vangle += 0.1 * theta;
			 }
			 //LIGHT TRANSFORMATIONS
			 else if (coordinate == 4 && type == 1) { //Light Rotate x
			 rx = 1;
			 ry = 0;
			 rz = 0;
			 Spot.rotateWC(rx, ry, rz, theta * 0.5);
			 } else if (coordinate == 4 && type == 2) { //Light Rotate y
			 rx = 0;
			 ry = 1;
			 rz = 0;
			 Spot.rotateWC(rx, ry, rz, theta * 0.5);
			 } else if (coordinate == 4 && type == 3) { //Light Rotate z
			 rx = 0;
			 ry = 0;
			 rz = 1;
			 Spot.rotateWC(rx, ry, rz, theta * 0.5);
			 } else if (coordinate == 4 && type == 4) { //Light Translate x
			 Spot.lx += theta * 0.02;
			 } else if (coordinate == 4 && type == 5) { //Light Translate y
			 Spot.ly += theta * 0.02;
			 } else if (coordinate == 4 && type == 6) { //Light Translate z
			 Spot.lz += theta * 0.02;
			 } else if (coordinate == 4 && type == 7) { // Ambient Ka
			 ambient[0] += theta * 0.01;
			 ambient[1] += theta * 0.01;
			 ambient[2] += theta * 0.01;
			 if (Spot.Ka > 1.0) {
			 Spot.Ka = 1.0;
			 } else if (Spot.Ka < 0) {
			 Spot.Ka = 0.0;
			 } else {
			 theta = (xBegin - x < 0) ? 1 : -1;
			 Spot.Ka += theta * 0.01;
			 }
			 }

			 else if (coordinate == 4 && type == 8) { // Ambient B
			 ambient[0] += theta * 0.01;
			 ambient[1] += theta * 0.01;
			 ambient[2] += theta * 0.01;

			 if (Spot.B > 1.0) {
			 Spot.B = 1.0;
			 } else if (Spot.B < 0) {
			 Spot.B = 0.0;
			 } else {
			 theta = (xBegin - x < 0) ? 1 : -1;
			 Spot.B += theta * 0.01;
			 }

			 }

			 else if (coordinate == 4 && type == 9) { // Point Light Kd
			 diffuse[0] += theta * 0.01;
			 diffuse[1] += theta * 0.01;
			 diffuse[2] += theta * 0.01;

			 if (Spot.Kd > 1.0) {
			 Spot.Kd = 1.0;
			 } else if (Spot.Kd < 0) {
			 Spot.Kd = 0.0;
			 } else {
			 theta = (xBegin - x < 0) ? 1 : -1;
			 Spot.Kd += theta * 0.01;
			 }

			 }

			 else if (coordinate == 4 && type == 10) { // Point Intensity P
			 diffuse[0] += theta * 0.01;
			 diffuse[1] += theta * 0.01;
			 diffuse[2] += theta * 0.01;
			 if (Spot.P > 1.0) {
			 Spot.P = 1.0;
			 } else if (Spot.P < 0) {
			 Spot.P = 0.0;
			 } else {
			 theta = (xBegin - x < 0) ? 1 : -1;
			 Spot.P += theta * 0.01;
			 }

			 }
			 */

		}
	}
	glutPostRedisplay();
}

/*
 void getPos(GLint x, GLint y) {
 GLint viewport[4];
 GLdouble modelview[16];
 GLdouble projection[16];
 GLfloat winX, winY, winZ;
 <<<<<<< HEAD

 glGetDoublev( GL_MODELVIEW_MATRIX, modelview);
 glGetDoublev( GL_PROJECTION_MATRIX, projection);
 glGetIntegerv( GL_VIEWPORT, viewport);

 =======

 glGetDoublev( GL_MODELVIEW_MATRIX, modelview);
 glGetDoublev( GL_PROJECTION_MATRIX, projection);
 glGetIntegerv( GL_VIEWPORT, viewport);

 >>>>>>> 75f39d7886e8ffd5bbfc8aebf7667660a05123cf
 winX = (float) x;
 winY = (float) viewport[3] - (float) y;
 glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

 gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX,
 &posY, &posZ);
 printf("%f %f posX: %f, posY: %f\n", x, y, posX, posZ);
 }

 */

/*-------ANIMATION FUNCTION-------------------*/
GLfloat ball_x_trans = 0.01, ball_y_trans = 0.00, ball_z_trans = 0.00;
//This function doesn't work as planned. Will fix tomorrow
GLint check_collision_aux(Cube* object) {
	GLfloat sphereP1[3];
	GLfloat radius = 0.2;
	GLint count = 0;
	sphereP1[0] = myWorld.ball->sphere_center_wc[0];
	sphereP1[1] = myWorld.ball->sphere_center_wc[1]; // + radius + ball_y_trans
	sphereP1[2] = (myWorld.ball->sphere_center_wc[2]);

	/*GLint i;
	 for(i = 0; i < 6; i++){
	 printf("%f, %f, %f \n", sphereP1[0], sphereP1[1], sphereP1[2]);
	 printf("%f, %f, %f \n", object->cube_face_center_wc[i][0], object->cube_face_center_wc[i][1], object->cube_face_center_wc[i][2]);
	 printf("%f, %f, %f \n", object->cube_face_norm_wc[i][0], object->cube_face_norm_wc[i][1], object->cube_face_norm_wc[i][2]);
	 //float result = ((object->cube_face_center_wc[i][0] - sphereP1[0]) * object->cube_face_norm_wc[i][0]) +
	 //		((object->cube_face_center_wc[i][1] - sphereP1[1]) * object->cube_face_norm_wc[i][1]) +
	 //		((object->cube_face_center_wc[i][2] - sphereP1[2]) * object->cube_face_norm_wc[i][2]);
	 GLfloat result = ((object->cube_center_wc[0] - sphereP1[0]) * object->cube_face_norm_wc[i][0]) +
	 ((object->cube_center_wc[1] - sphereP1[1]) * object->cube_face_norm_wc[i][1]) +
	 ((object->cube_center_wc[2] - sphereP1[2]) * object->cube_face_norm_wc[i][2]);

	 printf("%f \n", result);
	 if (result < 0) count++;
	 printf("%d, %d \n", i, count);
	 }
	 if (count == 6) return 1;*/
	GLint i;
	for (i = 0; i < 6; i++) {
		GLfloat facing_in = ((0 - object->cube_center_wc[0]) * (object->cube_face_center_wc[i][0] - object->cube_center_wc[0])) +
				((0 - object->cube_center_wc[1]) * (object->cube_face_center_wc[i][1] - object->cube_center_wc[1])) +
				((0 - object->cube_center_wc[2]) * (object->cube_face_center_wc[i][2] - object->cube_center_wc[2]));
		if (facing_in > 0) {
			printf("Face: %d... \n", i);
			//y-direction collisions
			if (i == 5 && (object->cube_face_center_wc[i][1] < sphereP1[1])) {
				printf("Cube face center y: %f, sphere y: %f \n",object->cube_face_center_wc[i][1], sphereP1[1]);
				ball_y_trans = ball_y_trans * -1;
			} else if (i == 4
					&& (object->cube_face_center_wc[i][1] > sphereP1[1])) {
				ball_y_trans = ball_y_trans * -1;
			}
			//x direction collisions
			else if (i == 3	&& (object->cube_face_center_wc[i][0] < (sphereP1[0]/2))) {
				printf("Cube face center x: %f, sphere x: %f \n",object->cube_face_center_wc[i][0], sphereP1[0]);
										ball_x_trans = ball_x_trans * -1;
			}
			else if (i == 1 && (object->cube_face_center_wc[i][0] > (sphereP1[0]/2))) {
							ball_x_trans = ball_x_trans * -1;
			}
			//z direction collisions
			else if (i == 0	&& (object->cube_face_center_wc[i][2] < sphereP1[2])) {
				ball_z_trans = ball_z_trans * -1;
			}
			else if (i == 2 && (object->cube_face_center_wc[i][2] > sphereP1[2])) {
				ball_z_trans = ball_z_trans * -1;
			}
		}
	}
	return 0;
}

void check_collision() {
	GLint n = 2;
	GLint found = 0, found2 = 0;
	while (n < 6 && found == 0 && found2 == 0) {
		printf("Object: %d, ", n);
		found = check_collision_aux(myWorld.list[n]);
		//found2 = check_collision_aux2(myWorld.list[n]);
		n++;
	}
	//if (found == 1 || found2 == 1) {
//	ball_y_trans = ball_y_trans * -1;
	//}
}

void move(void) {
	check_collision();
	/*
	 GLfloat rx, ry, rz, theta;

	 theta = 0.05;
	 rx = myWorld.ball->getMC().mat[0][1];
	 ry = myWorld.ball->getMC().mat[1][1];
	 rz = myWorld.ball->getMC().mat[2][1];
	 */
	myWorld.ball->translate(ball_x_trans, ball_y_trans, ball_z_trans);

	glutPostRedisplay();

}

int check = 2;
void ColorChange(int x) {
	if (check > 5) {
		check = 1;
		myWorld.list[2]->setColor(1.0, 1.0, 1.0);
		myWorld.list[3]->setColor(1.0, 1.0, 1.0);
		myWorld.list[4]->setColor(1.0, 1.0, 1.0);
		myWorld.list[5]->setColor(1.0, 1.0, 1.0);
	}
	/*
	 myWorld.list[2]->setColor(1.0, 1.0, 1.0);
	 myWorld.list[3]->setColor(1.0, 1.0, 1.0);
	 myWorld.list[4]->setColor(1.0, 1.0, 1.0);
	 myWorld.list[5]->setColor(1.0, 1.0, 1.0);
	 */
	else {
		myWorld.list[check]->setColor(1.0, 0.5, 0.0);
	}
	check++;
	if (x == 1) {
		glutTimerFunc(1000, ColorChange, 1);
	}
	glutPostRedisplay();

}

void Disable() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable( GL_NORMALIZE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glutIdleFunc(NULL);
	//glUseProgram(0);
}

void Enable() {
	glEnable(GL_DEPTH_TEST); // enable OpenGL depth buffer algorithm for hidden surface removal
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable( GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);
}

void ResetLightPosition() {
	GLfloat temp[] = { 1.8, 1.8, 1.5, 1.0 };
	GLfloat temp2[] = { 0.0, 0.0, 0.0, 1.0 };
	int i = 0;
	for (i = 0; i < 4; i++) {
		position[i] = temp[i];
		positionSolar[i] = temp2[i];
	}
}

void ResetLightValue() {
	GLfloat temp1[] = { 0.1, 0.1, 0.3, 1.0 };
	GLfloat temp2[] = { 0.6, 0.6, 1.0, 1.0 };
	GLfloat temp3[] = { 1.0, 1.0, 1.0, 1.0 };
	int i = 0;
	for (i = 0; i < 4; i++) {
		ambient[i] = temp1[i];
		diffuse[i] = temp2[i];
		specular[i] = temp3[i];
	}
}

void ResetLightAll() {
	ResetLightPosition();
	ResetLightValue();
}

/*-----------------------------------------------------------*/
void create_court() {
	//Play paddle
	myWorld.list[0]->setColor(1.0, 1.0, 1.0);
	myWorld.list[0]->scale_change(-0.75);
	myWorld.list[0]->scaleZ(-0.2);
	myWorld.list[0]->scaleX(0.1);
	myWorld.list[0]->translate(0, 0, 2.5);

	//Opponent Paddle
	myWorld.list[1]->setColor(1.0, 0.5, 0.5);
	myWorld.list[1]->scale_change(-0.75);
	myWorld.list[1]->scaleZ(-0.2);
	myWorld.list[1]->scaleX(0.1);
	myWorld.list[1]->translate(0, 0, -4.5);

	//Ball
	myWorld.ball->translate(0, 0, 0);
	myWorld.ball->scale_change(-0.8);

	//Left wall
	myWorld.list[2]->setColor(1.0, 0.5, 0.0);
	myWorld.list[2]->translate(-1.5, 0, 0);
	myWorld.list[2]->scaleX(-0.9);
	myWorld.list[2]->scaleZ(4.5);
	myWorld.list[2]->scaleY(0.5);

	//Top wall
	myWorld.list[3]->setColor(1.0, 1.0, 1.0);
	myWorld.list[3]->translate(0, 1.5, 0);
	myWorld.list[3]->scaleY(-0.9);
	myWorld.list[3]->scaleZ(4.5);
	myWorld.list[3]->scaleX(0.5);

	//Right wall
	myWorld.list[4]->setColor(0.0, 0.37647, 0.53333);
	myWorld.list[4]->translate(1.5, 0, 0);
	myWorld.list[4]->scaleX(-0.9);
	myWorld.list[4]->scaleZ(4.5);
	myWorld.list[4]->scaleY(0.5);

	//Bottom wall
	myWorld.list[5]->setColor(1.0, 1.0, 1.0);
	myWorld.list[5]->translate(0, -1.5, 0);
	myWorld.list[5]->scaleY(-0.9);
	myWorld.list[5]->scaleZ(4.5);
	myWorld.list[5]->scaleX(0.5);

}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);  // Set display-window color to black
	glMatrixMode(GL_PROJECTION);
	gluPerspective(myCam.vangle, 1.0, myCam.dnear, myCam.dfar);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(myCam.xeye, myCam.yeye, myCam.zeye, myCam.xref, myCam.yref,
			myCam.zref, myCam.Vx, myCam.Vy, myCam.Vz);
	glEnable(GL_DEPTH_TEST);
	//programObject = InitShader("vshader.glsl", "fshader.glsl");
	//glUseProgram(0);

	create_court();
}

/*-------MENUS------------------------------------------------------------*/

/*

 void MCTransMenu(GLint transOption) {
 coordinate = 1;
 type = transOption; //1 for rotate x, 2 for rotate y, 3 for rotate z, 4 for scale
 glutPostRedisplay();
 }

 void WCTransMenu(GLint transOption) {
 coordinate = 2;
 type = transOption; //1 rot x; 2 rot y; 3 rot z; 4 trans x; 5 trans y; 6 trans z
 glutPostRedisplay();
 }

 */

void mainMenu(GLint option) {
	switch (option) {
	case 1: { //reset
		/*
		 myWorld.list[0] = new Cube();

		 myCam.xeye = 3.0, myCam.yeye = 3.0, myCam.zeye = 7.0; //set view back to default!
		 myCam.vangle = 40.0, myCam.dnear = 2.0, myCam.dfar = 20.0;
		 Spot.resetAll();
		 Spot.off();
		 glutIdleFunc(NULL);
		 ResetLightAll();
		 Disable();
		 glutPostRedisplay();
		 */
		break;
	}
	case 2: {
		exit(0);
	}
		break;
	case 3: {
		if (game_start == 0) {
			game_start = 1;
			//ColorChange(1);
		} else {
			game_start = 0;

		}
	}
	}

}

/*
 void VCTransMenu(GLint transOption) {
 coordinate = 3;
 type = transOption; // 1 rotate x, 2 rotate y, 3 rotate z, 4 translate x, 5 translate y, 6 translate z, 7 clipping near, 8 clipping far, 9 angle
 glutPostRedisplay();
 }
 */

void colorSubMenu(GLint colorOption) {
	switch (colorOption) {
	case 1: { //White
		red = 1.0;
		green = 1.0;
		blue = 1.0;
		break;
	}
	case 2: { //Red
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		break;
	}
	case 3: { //Green
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		break;
	}
	case 4: { //Blue
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;
	}
	}
	glColor3f(red, green, blue);
	glutPostRedisplay();
}

/*

 void A3Menu(GLint faceOption) {
 switch (faceOption) {
 case 1: {
 glutIdleFunc(move);
 }
 break; // run the animation
 case 2: {
 glutIdleFunc(NULL);
 break;
 } // stop animation, and do other drawing

 case 3: { //Turn on Light
 Spot.on();
 break;
 }

 case 4: { //Turn off Light
 Spot.off();
 break;
 }

 case 5: { //Reset light position
 Spot.resetPosition();
 ResetLightPosition();

 break;
 }

 case 6: { //Reset light value
 Spot.resetIllumination();
 ResetLightValue();
 break;
 }

 case 7: { //Reset light ALL
 Spot.resetAll();
 ResetLightAll();
 break;
 }

 }
 glutPostRedisplay();
 }

 void LightTransMenu(GLint Option) {
 coordinate = 4;
 type = Option;
 }

 void glslSubMenu(GLint glslOption) {
 switch (glslOption) {
 case 1:
 //glUseProgram(programObject);

 break;
 case 2:
 //glUseProgram(0);

 break;
 default:
 break;
 }

 glutPostRedisplay();
 }

 void ObjMenu(GLint option) {
 switch (option) {
 case 1: { //Cube
 Enable();
 selected = 0;
 break;
 }

 case 2: {
 selected = 1;
 break;
 }

 case 3: {
 selected = 2;
 break;
 }
 case 4: { //Show Point Light
 Spot.pointOn();
 break;
 }

 case 5: { //Hide Point Light
 Spot.pointOff();
 break;
 }
 }
 glutPostRedisplay();
 }
 */
void printMenu(GLint x) {
	switch (x) {
	case 1:
		printf(
				"Dnear: %f Dfar: %f vAngle: %f xeye: %f, yeye: %f, zeye: %f, xref: %f, yref: %f, zref: %f\n",
				myCam.dnear, myCam.dfar, myCam.vangle, myCam.xeye, myCam.yeye,
				myCam.zeye, myCam.xref, myCam.yref, myCam.zref);
		break;
	}
}

void menu() {
	/*
	 GLint WCTrans_Menu, VCTrans_Menu, MCTrans_Menu, A3_Menu, LightTrans_Menu,
	 glsl_shad, Obj_Menu, Print_Menu;
	 */
	GLint Print_Menu;
	/*
	 MCTrans_Menu = glutCreateMenu(MCTransMenu);
	 glutAddMenuEntry(" Rotate x ", 1);
	 glutAddMenuEntry(" Rotate y ", 2);
	 glutAddMenuEntry(" Rotate z ", 3);
	 glutAddMenuEntry(" ScaleX ", 4);
	 glutAddMenuEntry(" ScaleY ", 5);
	 glutAddMenuEntry(" ScaleZ ", 6);
	 glutAddMenuEntry(" Scale All ", 7);

	 WCTrans_Menu = glutCreateMenu(WCTransMenu);
	 glutAddMenuEntry(" Rotate x ", 1);
	 glutAddMenuEntry(" Rotate y ", 2);
	 glutAddMenuEntry(" Rotate z", 3);
	 glutAddMenuEntry(" Translate x ", 4);
	 glutAddMenuEntry(" Translate y ", 5);
	 glutAddMenuEntry(" Translate z", 6);

	 VCTrans_Menu = glutCreateMenu(VCTransMenu);
	 glutAddMenuEntry(" Rotate x ", 1);
	 glutAddMenuEntry(" Rotate y ", 2);
	 glutAddMenuEntry(" Rotate z", 3);
	 glutAddMenuEntry(" Translate x ", 4);
	 glutAddMenuEntry(" Translate y ", 5);
	 glutAddMenuEntry(" Translate z", 6);
	 glutAddMenuEntry(" Clipping Near ", 7);
	 glutAddMenuEntry(" Clipping Far ", 8);
	 glutAddMenuEntry(" Angle ", 9);

	 A3_Menu = glutCreateMenu(A3Menu);
	 glutAddMenuEntry("Animation On", 1);
	 glutAddMenuEntry("Animation Off", 2);
	 glutAddMenuEntry("Cube Light On", 3);
	 glutAddMenuEntry("Cube Light Off", 4);
	 glutAddMenuEntry("Reset Light Position", 5);
	 glutAddMenuEntry("Reset Light Values", 6);
	 glutAddMenuEntry("Reset Light All", 7);

	 LightTrans_Menu = glutCreateMenu(LightTransMenu);
	 glutAddMenuEntry("Rotate x", 1);
	 glutAddMenuEntry("Rotate y", 2);
	 glutAddMenuEntry("Rotate z", 3);
	 glutAddMenuEntry("Translate x", 4);
	 glutAddMenuEntry("Translate y", 5);
	 glutAddMenuEntry("Translate z", 6);
	 glutAddMenuEntry("Ambient Ka", 7);
	 glutAddMenuEntry("Ambient B", 8);
	 glutAddMenuEntry("Point Light Kd", 9);
	 glutAddMenuEntry("Point Intensity P", 10);

	 glsl_shad = glutCreateMenu(glslSubMenu);
	 glutAddMenuEntry(" On ", 1);
	 glutAddMenuEntry(" Off ", 2);
	 */

	Print_Menu = glutCreateMenu(printMenu);
	glutAddMenuEntry(" Print View Variables ", 1);

	/*
	 Obj_Menu = glutCreateMenu(ObjMenu);
	 glutAddMenuEntry(" Cube ", 1);
	 glutAddMenuEntry(" Cube 2 ", 2);
	 glutAddMenuEntry(" Sphere ", 3);
	 glutAddMenuEntry(" Solar System Animation ", 3);
	 glutAddMenuEntry(" Show Point Light ", 4);
	 glutAddMenuEntry(" Hide Point Light ", 5);
	 */
	glutCreateMenu(mainMenu);      // Create main pop-up menu.

	/*
	 glutAddSubMenu(" GLSL ", glsl_shad);
	 glutAddSubMenu(" Model Transformations ", MCTrans_Menu);
	 glutAddSubMenu(" WC Transformations ", WCTrans_Menu);
	 glutAddSubMenu(" View Transformations ", VCTrans_Menu);
	 glutAddSubMenu(" Light Transformations ", LightTrans_Menu);
	 glutAddSubMenu(" Object Display ", Obj_Menu);
	 glutAddSubMenu(" Miscellaneous ", A3_Menu);
	 */
	glutAddSubMenu(" Print ", Print_Menu);
	//glutAddMenuEntry(" Reset ", 1);
	glutAddMenuEntry(" Game Start/Stop ", 3);
	glutAddMenuEntry(" Quit", 2);
}

/*-------MENUS END------------------------------------------------------------*/

/*----MAIN---------------------------*/
int main(int argc, char** argv) {
	//PlaySound((LPCSTR) "01 Do I Wanna Know.wav", NULL, SND_FILENAME | SND_ASYNC);
	//Song by Arctic Monkeys from their album called AM
	//Album can be purchased from iTunes

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("CP411 Final Project: CurveBall 2.0");
	glewInit();
	init();
	menu();

	glutDisplayFunc(display);
	glutIdleFunc(move);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}

