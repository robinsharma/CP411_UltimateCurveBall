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

GLint winWidth = 800, winHeight = 800;
/*  Set coordinate limits for the clipping window:  */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

/*  Set positions for near and far clipping planes:  */
GLfloat vangle = 40.0, dnear = 2.0, dfar = 20.0;
//GLfloat theta = 0.0, rx = 1.0, ry = 0.0, rz = 0.0, s=0.8;

GLfloat red = 1.0, green = 1.0, blue = 1.0;  //color
GLint moving = 0, xBegin = 0, coordinate = 1, type = 1, selected = 0;

//Declare a world containing all objects to draw.
World myWorld;
Light Spot;
Camera myCam;

wcPt3D ctrlPts[10]; // to store control points,
wcPt3D RBM[73][26], RBC_face_norm[73][26]; // to store the mesh points and norm at each points

GLint nCtrlPts = 0; // number control points selected
GLint R = 45, S = 5, T = 5; // Rotation variables
GLint Ptgen = 1, BCgen = 0, BCRotation = 1; // state variables for control point generation, Bezier curve generation, Bezier curve rotation

GLint style = 1;

//Lighting substitute lx, ly, lz
GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };
GLfloat positionSolar[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat ambient[] = { 0.1, 0.1, 0.3, 1.0 };
GLfloat diffuse[] = { 0.6, 0.6, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

//GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
//GLfloat local_view[] = { 0.0 };

//Material
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 1, 1, 1, 1 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1, 1, 1, 1 };

GLuint programObject;

bool SolarStarted = false; //boolean prevents solar animation from getting faster upon repeated selection

void rotateView(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix* m = new Matrix();
	m->rotate(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = xeye;
	v[1] = yeye;
	v[2] = zeye;
	v[3] = 1;
	m->multiply_vector(v);
	xeye = v[0];
	yeye = v[1];
	zeye = v[2];
	delete m;
}

void display(void) {

	if (BCRotation) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(vangle, 1.0, dnear, dfar);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(xeye, yeye, zeye, xref, yref, zref, Vx, Vy, Vz);

		if (Spot.getOn()) {
			glDisable(GL_LIGHTING);
		}

		glLineWidth(3);

		glBegin(GL_LINES);
		//x-axis
		glColor3f(0.0, 0.0, 1.0);
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
		glLineWidth(1);

		if (Spot.getOn()) {
			glEnable(GL_LIGHTING);
		} else
			glDisable(GL_LIGHTING);

		if (style == 2 && Spot.getOn()) {
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT0, GL_POSITION, position);

			glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
			glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		}

		myWorld.draw_world(); // draw all objects in the world
		Spot.draw();
	}

	else {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(vangle, 1.0, dnear, dfar);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(xeye, yeye, zeye, xref, yref, zref, Vx, Vy, Vz);

		glLineWidth(1.0);

		glColor3f(red, green, blue);

		myWorld.draw_world(); // draw all objects in the world
		Spot.draw();
	}

	glFlush();
	glutSwapBuffers();
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
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Ptgen == 1) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

			myWorld.myBezier->ctrlPts[myWorld.myBezier->nCtrlPts].x = x
					- winWidth / 2;
			myWorld.myBezier->ctrlPts[myWorld.myBezier->nCtrlPts].y = winHeight
					/ 2 - y;
			myWorld.myBezier->ctrlPts[myWorld.myBezier->nCtrlPts].z = 0;

			printf("Point %d set: %f %f \n", myWorld.myBezier->nCtrlPts,
					myWorld.myBezier->ctrlPts[myWorld.myBezier->nCtrlPts].x,
					myWorld.myBezier->ctrlPts[myWorld.myBezier->nCtrlPts].y);

			if (myWorld.myBezier->nCtrlPts < 10) {
				myWorld.myBezier->nCtrlPts++;
			}
		}
		glutPostRedisplay();
	}
}

void mouseMotion(GLint x, GLint y) {
	GLfloat rx, ry, rz, theta;
	if (moving) {
		theta = (xBegin - x > 0) ? 1 : -1;
		if (coordinate == 1 && type == 1) { // mc rotate x
			if (myWorld.isBez) {
				rx = myWorld.myBezier->getMC().mat[0][0];
				ry = myWorld.myBezier->getMC().mat[1][0];
				rz = myWorld.myBezier->getMC().mat[2][0];
				myWorld.myBezier->rotate_mc(rx, ry, rz, theta * 0.5);
			} else {
				rx = myWorld.list[selected]->getMC().mat[0][0];
				ry = myWorld.list[selected]->getMC().mat[1][0];
				rz = myWorld.list[selected]->getMC().mat[2][0];
				myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 0.5);
			}
		}

		else if (coordinate == 1 && type == 2) { // mc rotate y
			if (myWorld.isBez) {


			} else {
				rx = myWorld.list[selected]->getMC().mat[0][1];
				ry = myWorld.list[selected]->getMC().mat[1][1];
				rz = myWorld.list[selected]->getMC().mat[2][1];
				myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 0.5);
			}
		}

		else if (coordinate == 1 && type == 3) { // mc rotate z
			if (myWorld.isBez) {
				rx = myWorld.myBezier->getMC().mat[0][2];
				ry = myWorld.myBezier->getMC().mat[1][2];
				rz = myWorld.myBezier->getMC().mat[2][2];
				myWorld.myBezier->rotate_mc(rx, ry, rz, theta * 0.5);

			} else {
				rx = myWorld.list[selected]->getMC().mat[0][2];
				ry = myWorld.list[selected]->getMC().mat[1][2];
				rz = myWorld.list[selected]->getMC().mat[2][2];
				myWorld.list[selected]->rotate_mc(rx, ry, rz, theta * 0.5);
			}
		}

		else if (coordinate == 1 && type == 4) { // mc scale
			if (myWorld.isBez) {
				myWorld.myBezier->scale_change(theta * 0.02);
			} else {
				myWorld.list[selected]->scale_change(theta * 0.02);
			}
		}

		else if (coordinate == 2 && type == 1) { // wc rotate x

			rx = 1;
			ry = 0;
			rz = 0;
			if (myWorld.isBez) {
				myWorld.myBezier->rotate_origin(rx, ry, rz, theta * 0.5);
			} else {
				myWorld.list[selected]->rotate_origin(rx, ry, rz, theta * 0.5);
			}
		}

		else if (coordinate == 2 && type == 2) { // wc rotate y
			rx = 0;
			ry = 1;
			rz = 0;
			if (myWorld.isBez) {
				myWorld.myBezier->rotate_origin(rx, ry, rz, theta * 0.5);
			} else {
				myWorld.list[selected]->rotate_origin(rx, ry, rz, theta * 0.5);
			}
		}

		else if (coordinate == 2 && type == 3) { //wc rotate z
			rx = 0;
			ry = 0;
			rz = 1;
			if (myWorld.isBez) {
				myWorld.myBezier->rotate_origin(rx, ry, rz, theta * 0.5);
			} else {
				myWorld.list[selected]->rotate_origin(rx, ry, rz, theta * 0.5);
			}
		}

		else if (coordinate == 2 && type == 4) { //wc translate x
			if (myWorld.isBez) {
				myWorld.myBezier->translate(theta * 0.02, 0, 0);
			} else {
				myWorld.list[selected]->translate(theta * 0.02, 0, 0);
			}
		}

		else if (coordinate == 2 && type == 5) { //wc translate y
			if (myWorld.isBez) {
				myWorld.myBezier->translate(0, theta * 0.02, 0);

			} else {
				myWorld.list[selected]->translate(0, theta * 0.02, 0);
			}
		}

		else if (coordinate == 2 && type == 6) { //wc translate z
			if (myWorld.isBez) {
				myWorld.myBezier->translate(0, 0, theta * 0.02);

			} else {
				myWorld.list[selected]->translate(0, 0, theta * 0.02);
			}
		}

		else if (coordinate == 3 && type == 1) { //VC Rotate x

			rx = 1;
			ry = 0;
			rz = 0;

			rotateView(rx, ry, rz, theta);
		}

		else if (coordinate == 3 && type == 2) { //VC Rotate y

			rx = 0;
			ry = 1;
			rz = 0;

			rotateView(rx, ry, rz, theta);

		}

		else if (coordinate == 3 && type == 3) { //VC Rotate z

			rx = 0;
			ry = 0;
			rz = 1;

			rotateView(rx, ry, rz, theta);

		}

		else if (coordinate == 3 && type == 4) { //VC Translate x

			xeye += 0.1 * theta;

		} else if (coordinate == 3 && type == 5) { //VC Translate y

			yeye += 0.1 * theta;

		} else if (coordinate == 3 && type == 6) { //VC Translate z
			zeye += 0.1 * theta;
		}

		else if (coordinate == 3 && type == 7) { //VC Clipping Near
			theta = (xBegin - x < 0) ? 1 : -1;
			dnear += 0.1 * theta;
		}

		else if (coordinate == 3 && type == 8) { //VC Clipping Far
			dfar += 0.1 * theta;

		}

		else if (coordinate == 3 && type == 9) { //Angle
			vangle += 0.1 * theta;
		}

		//LIGHT TRANSFORMATIONS
		else if (coordinate == 4 && type == 1) { //Light Rotate x
			rx = 1;
			ry = 0;
			rz = 0;
			Spot.rotateWC(rx, ry, rz, theta * 0.5);
			position[0] = Spot.lx;
			position[1] = Spot.ly;
			position[2] = Spot.lz;
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
			position[0] = Spot.lx;
			position[1] = Spot.ly;
			position[2] = Spot.lz;
		}

		else if (coordinate == 4 && type == 4) { //Light Translate x
			Spot.lx += theta * 0.02;
			position[0] = Spot.lx;
			position[1] = Spot.ly;
			position[2] = Spot.lz;

		}

		else if (coordinate == 4 && type == 5) { //Light Translate y
			Spot.ly += theta * 0.02;
			position[0] = Spot.lx;
			position[1] = Spot.ly;
			position[2] = Spot.lz;
		}

		else if (coordinate == 4 && type == 6) { //Light Translate z
			Spot.lz += theta * 0.02;
			position[0] = Spot.lx;
			position[1] = Spot.ly;
			position[2] = Spot.lz;

		}

		else if (coordinate == 4 && type == 7) { // Ambient Ka
			if (myWorld.isBez) {
				ambient[0] += theta * 0.01;
				ambient[1] += theta * 0.01;
				ambient[2] += theta * 0.01;
			} else {
				if (Spot.Ka > 1.0) {
					Spot.Ka = 1.0;
				} else if (Spot.Ka < 0) {
					Spot.Ka = 0.0;
				} else {
					theta = (xBegin - x < 0) ? 1 : -1;
					Spot.Ka += theta * 0.01;
				}
			}
		}

		else if (coordinate == 4 && type == 8) { // Ambient B
			if (myWorld.isBez) {
				ambient[0] += theta * 0.01;
				ambient[1] += theta * 0.01;
				ambient[2] += theta * 0.01;
			} else {
				if (Spot.B > 1.0) {
					Spot.B = 1.0;
				} else if (Spot.B < 0) {
					Spot.B = 0.0;
				} else {
					theta = (xBegin - x < 0) ? 1 : -1;
					Spot.B += theta * 0.01;
				}
			}

		}

		else if (coordinate == 4 && type == 9) { // Point Light Kd
			if (myWorld.isBez) {
				diffuse[0] += theta * 0.01;
				diffuse[1] += theta * 0.01;
				diffuse[2] += theta * 0.01;
			} else {
				if (Spot.Kd > 1.0) {
					Spot.Kd = 1.0;
				} else if (Spot.Kd < 0) {
					Spot.Kd = 0.0;
				} else {
					theta = (xBegin - x < 0) ? 1 : -1;
					Spot.Kd += theta * 0.01;
				}
			}
		}

		else if (coordinate == 4 && type == 10) { // Point Intensity P
			if (myWorld.isBez) {
				diffuse[0] += theta * 0.01;
				diffuse[1] += theta * 0.01;
				diffuse[2] += theta * 0.01;
			} else {
				if (Spot.P > 1.0) {
					Spot.P = 1.0;
				} else if (Spot.P < 0) {
					Spot.P = 0.0;
				} else {
					theta = (xBegin - x < 0) ? 1 : -1;
					Spot.P += theta * 0.01;
				}
			}

		}

		glutPostRedisplay();
	}

}
/*-------ANIMATION FUNCTION-------------------*/
void solarMove(int x) {
	GLfloat rx, ry, rz;

	myWorld.mySolar->Sun->rotate(0, -1, 0, 5);

	rx = myWorld.mySolar->Earth->getMC().mat[0][0];
	ry = myWorld.mySolar->Earth->getMC().mat[1][0];
	rz = myWorld.mySolar->Earth->getMC().mat[2][0];

	myWorld.mySolar->Earth->rotate_mc(rx, ry, rz, 5);
	myWorld.mySolar->Earth->rotate_origin(0, -1, 0, 5);

	rx = myWorld.mySolar->Moon->getMC().mat[0][0];
	ry = myWorld.mySolar->Moon->getMC().mat[1][0];
	rz = myWorld.mySolar->Moon->getMC().mat[2][0];

	myWorld.mySolar->Moon->rotate_mc(rx, ry, rz, 5);
	myWorld.mySolar->Moon->rotate_origin(0, -1, 0, 5);

	rx = myWorld.mySolar->Earth->getMC().mat[0][3];
	ry = myWorld.mySolar->Earth->getMC().mat[1][3];
	rz = myWorld.mySolar->Earth->getMC().mat[2][3];
	myWorld.mySolar->Moon->rotate_relative(rx, ry, rz, 0, -1, 0, 2);
	if (x == 1) {
		glutTimerFunc(40, solarMove, 1);
		SolarStarted = true;
	}
	glutPostRedisplay();

}

void move(void) {
	GLfloat rx, ry, rz, theta;

	theta = 0.05;

	if(!myWorld.isBez) {
		rx = myWorld.list[selected]->getMC().mat[0][1];
		ry = myWorld.list[selected]->getMC().mat[1][1];
		rz = myWorld.list[selected]->getMC().mat[2][1];
	myWorld.list[selected]->rotate_mc(rx, ry, rz, theta);
	}

	else {
		rx = myWorld.myBezier->getMC().mat[0][1];
		ry = myWorld.myBezier->getMC().mat[1][1];
		rz = myWorld.myBezier->getMC().mat[2][1];
		myWorld.myBezier->rotate_mc(rx, ry, rz, theta);

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
	glUseProgram(0);
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

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);  // Set display-window color to black
	glMatrixMode(GL_PROJECTION);
	gluPerspective(vangle, 1.0, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(xeye, yeye, zeye, xref, yref, zref, Vx, Vy, Vz);
	glEnable(GL_DEPTH_TEST);
	programObject = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(0);
}

/*-------MENUS------------------------------------------------------------*/

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

void mainMenu(GLint option) {
	switch (option) {
	case 1: { //reset
		myWorld.list[0] = new Cube();
		myWorld.myBezier = new Bezier();
		myWorld.isBez = true;
		xeye = 3.0, yeye = 3.0, zeye = 7.0; //set view back to default!
		vangle = 40.0, dnear = 2.0, dfar = 20.0;
		Spot.resetAll();
		Spot.off();
		glutIdleFunc(NULL);
		myWorld.solarAnimationOn = false;
		ResetLightAll();
		Disable();
		glutPostRedisplay();
		break;
	}
	case 2: {
		exit(0);
	}
	}

}

void VCTransMenu(GLint transOption) {
	coordinate = 3;
	type = transOption; // 1 rotate x, 2 rotate y, 3 rotate z, 4 translate x, 5 translate y, 6 translate z, 7 clipping near, 8 clipping far, 9 angle
	glutPostRedisplay();
}

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

void a4SubMenu(GLint A4Option) {
	myWorld.isBez = true;
	myWorld.solarAnimationOn = false;
	switch (A4Option) {
	case 1: {
		Ptgen = 1;
		BCgen = 0;
		BCRotation = 0;

		Disable();

	}
		break;
	case 2: {
		Ptgen = 0;
		BCgen = 1;
		BCRotation = 0;

		Disable();
	}
		break;
	case 3: {

		Ptgen = 0;
		BCgen = 0;
		BCRotation = 1;
		MCTransMenu(1);
		Disable();

	}
		break;
	case 4: {
		style = 1;
		Spot.off();
		Ptgen = 0;
		BCgen = 0;
		BCRotation = 1;
		Disable();

	}
		break;
	case 5: {
		Spot.on();
		style = 2;
		Ptgen = 0;
		BCgen = 0;
		BCRotation = 1;
		Enable();

	}
		break;
	case 6: {
		glClearColor(0.0, 0.0, 0.0, 1.0); // Set display-window color to black
		glMatrixMode(GL_PROJECTION);
		gluPerspective(vangle, 1.0, dnear, dfar);

		glMatrixMode(GL_MODELVIEW);

		gluLookAt(xeye, yeye, zeye, xref, yref, zref, Vx, Vy, Vz);

		Ptgen = 0;
		BCgen = 0;
		BCRotation = 0;

		myWorld.solarAnimationOn = true;
		Spot.pointOff();
		if (!SolarStarted) {
			solarMove(1);
		}

		glEnable(GL_DEPTH_TEST);

		glEnable( GL_NORMALIZE);

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

		// Set up simple lighting model
		glEnable( GL_LIGHTING);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, positionSolar);
		glEnable( GL_LIGHT0);

		// Enable material properties for lighting
		glEnable( GL_COLOR_MATERIAL);
		glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		glPixelStorei( GL_UNPACK_ALIGNMENT, 1);

		glEnable( GL_CULL_FACE);
		glEnable( GL_TEXTURE_2D);
		break;
	}
	}

	glutPostRedisplay();

}

void rotSubMenu(GLint rotOption) {
	switch (rotOption) {
	case 1:
		R = 45;
		break;
	case 2:
		R = 90;
		break;
	case 3:
		R = 135;
		break;
	case 4:
		R = 180;
		break;
	case 5:
		R = 225;
		break;
	case 6:
		R = 270;
		break;
	case 7:
		R = 315;
		break;
	case 8:
		R = 360;
		break;
	case 9:
		S = 5;
		break;
	case 10:
		S = 10;
		break;
	case 11:
		S = 15;
		break;
	case 12:
		T = 5;
		break;
	case 13:
		T = 10;
		break;
	case 14:
		T = 15;
		break;
	case 15:
		T = 20;
		break;
	case 16:
		T = 25;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void glslSubMenu(GLint glslOption) {
	switch (glslOption) {
	case 1:
		if (Ptgen != 1 && BCgen != 1 && style !=1) {
			glUseProgram(programObject);
		}

		break;
	case 2:
		glUseProgram(0);

		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void ObjMenu(GLint option) {
	switch (option) {
	case 1: { //Cube
		myWorld.isBez = false;
		myWorld.solarAnimationOn = false;
		Ptgen = 0;
		BCgen = 0;
		Enable();
		break;
	}
	case 2: { //Bezier
		myWorld.isBez = true;
		myWorld.solarAnimationOn = false;
		Disable();
		Ptgen = 1;
		BCgen = 0;
		break;
	}
	case 3: { //Solar System
		a4SubMenu(6);
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

void AxisMenu(GLint option) {
	BCRotation = option;
	glutPostRedisplay();
}

void menu() {
	GLint WCTrans_Menu, VCTrans_Menu, MCTrans_Menu, A3_Menu, LightTrans_Menu,
			Rot_Menu, glsl_shad, A4_Menu, Axis_Menu, Obj_Menu;
	MCTrans_Menu = glutCreateMenu(MCTransMenu);
	glutAddMenuEntry(" Rotate x ", 1);
	glutAddMenuEntry(" Rotate y ", 2);
	glutAddMenuEntry(" Rotate z", 3);
	glutAddMenuEntry(" Scale", 4);

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

	Rot_Menu = glutCreateMenu(rotSubMenu);
	glutAddMenuEntry(" R->45 ", 1);
	glutAddMenuEntry(" R->90 ", 2);
	glutAddMenuEntry(" R->135 ", 3);
	glutAddMenuEntry(" R->180 ", 4);
	glutAddMenuEntry(" R->225 ", 5);
	glutAddMenuEntry(" R->270 ", 6);
	glutAddMenuEntry(" R->315 ", 7);
	glutAddMenuEntry(" R->360 ", 8);
	glutAddMenuEntry(" S->5 ", 9);
	glutAddMenuEntry(" S->10 ", 10);
	glutAddMenuEntry(" S->15 ", 11);
	glutAddMenuEntry(" T->5 ", 12);
	glutAddMenuEntry(" T->10 ", 13);
	glutAddMenuEntry(" T->15 ", 14);
	glutAddMenuEntry(" T->20 ", 15);
	glutAddMenuEntry(" T->25 ", 16);

	glsl_shad = glutCreateMenu(glslSubMenu);
	glutAddMenuEntry(" On ", 1);
	glutAddMenuEntry(" Off ", 2);

	A4_Menu = glutCreateMenu(a4SubMenu);
	glutAddMenuEntry(" Control Point Selection ", 1);
	glutAddMenuEntry(" Bezier Curve Generation ", 2);
	glutAddMenuEntry(" X-axis rotate ", 3);
	glutAddSubMenu(" Rotation Options ", Rot_Menu);
	glutAddMenuEntry(" Mesh Without Lighting ", 4);
	glutAddMenuEntry(" Solid With Lighting ", 5);
	glutAddSubMenu(" GLSL Shading ", glsl_shad);
	glutAddMenuEntry(" A4P2: Solar System ", 6);

	Axis_Menu = glutCreateMenu(AxisMenu);
	glutAddMenuEntry(" Axis on ", 1);
	glutAddMenuEntry(" Axis off ", 0);

	Obj_Menu = glutCreateMenu(ObjMenu);
	glutAddMenuEntry(" Cube ", 1);
	glutAddMenuEntry(" Bezier ", 2);
	glutAddMenuEntry(" Solar System Animation ", 3);
	glutAddMenuEntry(" Show Point Light ", 4);
	glutAddMenuEntry(" Hide Point Light ", 5);

	glutCreateMenu(mainMenu);      // Create main pop-up menu.
	glutAddSubMenu(" A4 ", A4_Menu);
	glutAddSubMenu(" Model Transformations ", MCTrans_Menu);
	glutAddSubMenu(" WC Transformations ", WCTrans_Menu);
	glutAddSubMenu(" View Transformations ", VCTrans_Menu);
	glutAddSubMenu(" Light Transformations ", LightTrans_Menu);
	glutAddSubMenu(" Axis ", Axis_Menu);
	glutAddSubMenu(" Object Display ", Obj_Menu);
	glutAddSubMenu(" Miscellaneous ", A3_Menu);
	glutAddMenuEntry(" Reset ", 1);
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
	glutCreateWindow("CP411 Assignment 4 By Robin Sharma");
	glewInit();
	init();
	menu();

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}

