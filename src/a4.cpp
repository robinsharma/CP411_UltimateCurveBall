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
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Angel.h"

#include <GL/glut.h>

#include "World.hpp"
#include "Camera.hpp"

void mouseMotion(GLint, GLint);
bool loadbmp(UINT textureArray[], LPSTR strFileName, int ID);
void check_collision();
void move();
void reset();
void backgroundColor(GLint);
void setCurve(GLint, GLint, GLint, GLint);

GLint winWidth = 800, winHeight = 800;
/*  Set coordinate limits for the clipping window:  */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

/*  Set positions for near and far clipping planes:  */
GLfloat red = 1.0, green = 1.0, blue = 1.0;  //color
GLint moving = 0, start = 0, xBegin = 0, yBegin = 0, coordinate = 1, type = 1,
		selected = 0, game_start = 0, missed = 0;
GLboolean whiteBackground = false;
//Curve related variables
GLboolean check_curve = false;
const GLfloat SUPER = 0.0005;
const GLfloat REGULAR = 0.0002;
const GLint AILIVES = 3;
const GLint PLAYERLIVES = 5;
GLfloat curvex, curvey;
GLint begin, end;
GLint xCurve1, xCurve2, yCurve1, yCurve2;
GLint playerLives = 5, aiLives = AILIVES, level = 1;

//Declare a world containing all objects to draw.
World myWorld;
Light Spot;
Camera myCam;

//Lighting substitute lx, ly, lz
GLfloat position[] = { 1.8, 1.8, 1.5, 1.0 };

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

GLint Game_time = 0;
GLint speed = 1;
GLboolean printStart = true, game_over = false;

const GLint REGSCORE = 50;
const GLint SUPERSCORE = 100;
const GLint HIT = 25;
const GLint TAKELIFE = 150;
const GLint LEVELUP = 200;
GLint score = 0;

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(myCam.vangle, 1.0, myCam.dnear, myCam.dfar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(myCam.xeye, myCam.yeye, myCam.zeye, myCam.xref, myCam.yref,
			myCam.zref, myCam.Vx, myCam.Vy, myCam.Vz);

	Spot.on(); //turn on light
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

		char filename[] = "whiteline.bmp";
		loadbmp(textures, filename, 0);

		char filename1[] = "lines2.bmp";
		loadbmp(textures, filename1, 1);

		char filename2[] = "whiteline1.bmp";
		loadbmp(textures, filename2, 2);

		char filename3[] = "lines.bmp";
		loadbmp(textures, filename3, 3);

		char filename4[] = "Paddle.bmp";
		loadbmp(textures, filename4, 4);

		char filename5[] = "Paddle2.bmp";
		loadbmp(textures, filename5, 5);

		if (whiteBackground) {

			backgroundColor(2);

		} else {
			backgroundColor(1);
		}
		myWorld.list[0]->textureID = 4; //player paddle
		myWorld.list[1]->textureID = 5; //player paddle
		texturesLoaded = true; //only need to load up textures once
	}
	myWorld.draw_world(); // draw all objects in the world
	Spot.draw();

	//Print text to screen
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	if (printStart) {
			string start = "Start";
			//ostringstream sstm;
			//sstm << name;
			//string result;
			//result = sstm.str();
			//const char* c;
			glRasterPos2f(380, 390);
			for (string::iterator i = start.begin(); i != start.end(); ++i) {
				char c = *i;
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
			}

		//renderBitmapString(winWidth/2, winHeight/4, GLUT_BITMAP_HELVETICA_18, result.c_str());
	} else {
		std::ostringstream l;
		l << "Level: " << level;
		string lv = l.str();
		glRasterPos2f(20, 10);
		for (string::iterator i = lv.begin(); i != lv.end(); ++i) {
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
		std::ostringstream pl;
		pl << "Player Lives: " << playerLives;
		string player_lives = pl.str();
		glRasterPos2f(20, 780);
		for (string::iterator i = player_lives.begin(); i != player_lives.end(); ++i) {
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}
		std::ostringstream ol;
		ol << "Opponent Lives: " << aiLives;
		string ai_lives = ol.str();
		glRasterPos2f(620, 780);
		for (string::iterator i = ai_lives.begin(); i != ai_lives.end(); ++i) {
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}

		std::ostringstream sc;
		sc << "Score: " << score;
		string score_player = sc.str();
		glRasterPos2f(660, 10);
		for (string::iterator i = score_player.begin(); i != score_player.end(); ++i) {
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
		}

	}
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
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
		GLfloat width = winWidth * 0.2775;
		GLfloat height  = winHeight * 0.2;
		if ((x > (winWidth/2-width/2) && x < (winWidth/2+width/2)) && (y > (winHeight/2-height/2) && y < (winHeight/2+height/2))) {
			moving = 1;
			xBegin = x;
			yBegin = y;
			game_start = 1;
			glutIdleFunc(move);
			printStart = false;

		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		//moving = 0;
	}
	glutPostRedisplay();

}

void mouseMotion(GLint x, GLint y) {
	GLfloat thetaX, thetaY;
	if (moving == 1) {
		if (game_start == 1) {
			thetaX = (x - xBegin); //> 0) ? 1 : -1;
			thetaY = (yBegin - y); //> 0) ? 1 : -1;
			myWorld.list[0]->translate(thetaX * 0.003, 0, 0);
			myWorld.list[0]->translate(0, thetaY * 0.003, 0);
			xBegin = x;
			yBegin = y;
			if(check_curve == true){
				end = glutGet(GLUT_ELAPSED_TIME);
				if ((end - begin) > 30) {
					xCurve2 = x;
					yCurve2 = y;
					check_curve = false;
					setCurve(xCurve1, yCurve1, xCurve2, yCurve2);
				}
			}
		}
	}
	glutPostRedisplay();
}

void setCurve(GLint x1, GLint y1, GLint x2, GLint y2) {
	GLint diffx = x2 - x1;
	GLint diffy = y2 - y1;
	if (diffx < 0) {
		if (diffx <= -5 && diffx >= -10 ) {
			//Negative difference. Paddle moved from right to left. x curve positive
			//regular
			curvex = REGULAR;
			score += REGSCORE;

		} else if (diffx < -10) {
			//super curve positive x
			curvex = SUPER;
			score += SUPERSCORE;
		}
	} else if (diffx > 0) {
		if (diffx >= 5 && diffx <= 10) {
			//regular curve neg x
			curvex = -REGULAR;
			score += REGSCORE;
		} else if (diffx > 10) {
			//super curve neg x
			curvex = -SUPER;
			score += SUPERSCORE;
		}
	}

	if (diffy < 0) {
		if (diffy <= -5 && diffy >= -10 ) {
			//Negative difference. Paddle moved from bottom to top. y curve positive
			//regular
			curvey = -REGULAR;
			score += REGSCORE;
		} else if (diffy < -10) {
			//super curve positive y
			curvey = -SUPER;
			score += SUPERSCORE;
		}
	} else if (diffy > 0) {
		if (diffy >= 5 && diffy <= 10) {
			//regular curve neg y
			curvey = REGULAR;
			score += REGSCORE;
		} else if (diffy > 10) {
			//super curve neg y
			curvey = SUPER;
			score += SUPERSCORE;
		}
	}
}

/*-------ANIMATION FUNCTION-------------------*/
GLfloat ball_x_trans = 0.00, ball_y_trans = 0.00, ball_z_trans = 0.12;

void check_collision_paddles(Cube* object, int paddle) {
	GLfloat sphereP1[3];
	GLfloat radius = 0.2;
	sphereP1[0] = myWorld.ball->sphere_center_wc[0];
	sphereP1[1] = myWorld.ball->sphere_center_wc[1]; // + radius + ball_y_trans
	sphereP1[2] = myWorld.ball->sphere_center_wc[2];
	if (paddle == 0){//user paddle
		//Has not collided with front of paddle and has collided with the back wall.
		if(object->cube_face_center_wc[2][2] <  (sphereP1[2] + radius)){
			myWorld.ball->changeColor(1.0,0.0,0.0);
			ball_x_trans = 0;
			ball_y_trans = 0;
			ball_z_trans = 0;
			glutPostRedisplay();
			playerLives--;
			if(playerLives > 0){
				Sleep(1000);
				reset();
			}
			else{
				reset();
				moving = 0;
				game_start = 0;
				game_over = true;
				glutIdleFunc(NULL);
			}
			printf("Player Lives: %d. \n", playerLives);
			//return;
		}
		//check if colliding with z-axis of paddle
		else if(object->cube_face_center_wc[0][2] <  (sphereP1[2] + radius)){
			//check x and y axis to see if contact made with paddle or a MISS
			if(((object->cube_face_center_wc[1][0] + 0.1) > sphereP1[0] && (object->cube_face_center_wc[3][0] - 0.1) < sphereP1[0]) &&
				((object->cube_face_center_wc[5][1] - 0.1) < sphereP1[1] && (object->cube_face_center_wc[4][1]+ 0.1) > sphereP1[1])){
				check_curve = true;
				begin = glutGet(GLUT_ELAPSED_TIME);
				xCurve1 = xBegin;
				yCurve1 = yBegin;
				ball_z_trans = ball_z_trans * -1;
				curvex = 0.0;
				curvey = 0.0;
				score += HIT;
				PlaySound((LPCSTR) "Blop.wav", NULL, SND_FILENAME | SND_ASYNC);

			}
		}
	}
	else if(paddle == 1){
		//Has not collided with front of paddle and has collided with the back wall.
		if(object->cube_face_center_wc[0][2] >  (sphereP1[2] - radius)){
			myWorld.ball->changeColor(1.0,0.0,0.0);
			ball_x_trans = 0;
			ball_y_trans = 0;
			ball_z_trans = 0;
			glutPostRedisplay();
			aiLives--;
			score += TAKELIFE;
			printf("AI Lives: %d... Level: %d. \n",aiLives, level);
			if(aiLives == 0){
				level++;
				score += LEVELUP;
				aiLives = AILIVES;
			}
			Sleep(1000);
			reset();
			//return;
		}
		//check if colliding with z-axis of paddle
		else if(object->cube_face_center_wc[2][2] >  (sphereP1[2] - radius)){
			if(missed == 0){
				//check x and y axis to see if contact madle with paddle
				if(((object->cube_face_center_wc[1][0] + 0.1) > sphereP1[0] && (object->cube_face_center_wc[3][0] - 0.1) < sphereP1[0]) &&
					((object->cube_face_center_wc[5][1] - 0.11) < sphereP1[1] && (object->cube_face_center_wc[4][1]+ 0.1) > sphereP1[1])){
					ball_z_trans = ball_z_trans * -1;
					curvex = 0.0;
					curvey = 0.0;
					PlaySound((LPCSTR) "Blop.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				else{
					missed = 1;
				}
			}
		}
	}
}

//This function doesn't work as planned. Will fix tomorrow
void check_collision_wall(Cube* object) {
	GLfloat sphereP1[3];
	GLfloat radius = 0.2;
	//GLint count = 0;
	sphereP1[0] = myWorld.ball->sphere_center_wc[0];
	sphereP1[1] = myWorld.ball->sphere_center_wc[1]; // + radius + ball_y_trans
	sphereP1[2] = (myWorld.ball->sphere_center_wc[2]);

	GLint i;
	for (i = 0; i < 6; i++) {
		GLfloat facing_in = ((0 - object->cube_center_wc[0]) * (object->cube_face_center_wc[i][0] - object->cube_center_wc[0])) +
				((0 - object->cube_center_wc[1]) * (object->cube_face_center_wc[i][1] - object->cube_center_wc[1])) +
				((0 - object->cube_center_wc[2]) * (object->cube_face_center_wc[i][2] - object->cube_center_wc[2]));
		if (facing_in > 0) {
			//y-direction collisions
			if (i == 5 && (object->cube_face_center_wc[i][1] < (sphereP1[1] + radius))) {
				ball_y_trans = ball_y_trans * -1;
				PlaySound((LPCSTR) "Blop.wav", NULL, SND_FILENAME | SND_ASYNC);
			} else if (i == 4
					&& (object->cube_face_center_wc[i][1] > (sphereP1[1] - radius))) {
				ball_y_trans = ball_y_trans * -1;
				PlaySound((LPCSTR) "Blop.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
			//x direction collisions
			else if (i == 3	&& (object->cube_face_center_wc[i][0] < (sphereP1[0] + radius))) {
				ball_x_trans = ball_x_trans * -1;
				PlaySound((LPCSTR) "Blop.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (i == 1 && (object->cube_face_center_wc[i][0] > (sphereP1[0] - radius))) {
				ball_x_trans = ball_x_trans * -1;
				PlaySound((LPCSTR) "Blop.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
			//z direction collisions
			else if (i == 0	&& (object->cube_face_center_wc[i][2] < (sphereP1[2] + radius))) {
				ball_z_trans = ball_z_trans * -1;
				PlaySound((LPCSTR) "Blop.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (i == 2 && (object->cube_face_center_wc[i][2] > (sphereP1[2] - radius))) {
				ball_z_trans = ball_z_trans * -1;
				PlaySound((LPCSTR) "Blop.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
		}
	}
}

void check_collision() {
	GLint n = 0;
	//check paddles
	while(n < 2){
		check_collision_paddles(myWorld.list[n],n);
		n++;
	}
	// n now equals 2. Check walls
	while (n < 6) {
		check_collision_wall(myWorld.list[n]);
		n++;
	}
}

void move(void) {
	check_collision();
	Game_time += 1;
	if (Game_time % speed == 0) {
		//Move ball in the proper direction

		//if(curving_s == true){
			ball_x_trans += curvex;
		//}
		//else if(curving_r == true){
			ball_y_trans += curvey;
		//}
		myWorld.ball->translate(ball_x_trans, ball_y_trans, ball_z_trans);
		//move opponents paddle in relation to ball (NO Z TRANSLATION!)
		myWorld.list[1]->translate(ball_x_trans/2, ball_y_trans/2, 0);
		myWorld.tracker->translate(0,0,ball_z_trans);
		glutPostRedisplay();
	}
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

/*-----------------------------------------------------------*/
void create_court() {
	//Play paddle
	myWorld.list[0]->setColor(1.0, 1.0, 1.0);
	myWorld.list[0]->scale_change(-0.75);
	myWorld.list[0]->scaleZ(-0.1);
	myWorld.list[0]->scaleX(0.1);
	myWorld.list[0]->translate(0, 0, 2.5);

	//Opponent Paddle
	myWorld.list[1]->setColor(1.0, 0.5, 0.5);
	myWorld.list[1]->scale_change(-0.75);
	myWorld.list[1]->scaleZ(-0.1);
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
	//myWorld.list[5]->setColor(0.0, 0.37647, 0.53333);
	myWorld.list[5]->setColor(0.47, 0.333, 0.333);

	myWorld.list[5]->translate(0, -1.5, 0);
	myWorld.list[5]->scaleY(-0.9);
	myWorld.list[5]->scaleZ(4.5);
	myWorld.list[5]->scaleX(0.5);

	myWorld.tracker->scaleY(0.3);
	myWorld.tracker->scaleX(0.3);
	myWorld.tracker->translate(0,0,0.0);
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);  // Set display-window color to black
	glMatrixMode(GL_PROJECTION);
	gluPerspective(myCam.vangle, 1.0, myCam.dnear, myCam.dfar);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(myCam.xeye, myCam.yeye, myCam.zeye, myCam.xref, myCam.yref,
			myCam.zref, myCam.Vx, myCam.Vy, myCam.Vz);
	glEnable(GL_DEPTH_TEST);
	programObject = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(0);

	create_court();
}

void reset(){
	myWorld.reset();
	create_court();
	missed = 0;
	moving = 0;
	game_start = 0;
	glutIdleFunc(NULL);
	texturesLoaded = false;
	ball_x_trans = 0.00, ball_y_trans = 0.00, ball_z_trans = 0.1;
	curvex = 0.0, curvey = 0.0;
	check_curve = false;
	glutPostRedisplay();
}

void new_game(){
	playerLives = PLAYERLIVES;
	aiLives = AILIVES;
	level = 1;
	reset();
}

/*-------MENUS------------------------------------------------------------*/

void keyPressed (unsigned char key, int x, int y) {
	if (key == ' ') {
		if (game_start == 1) {
			game_start = 0;
			glutIdleFunc(NULL);
		} else {
			if (moving != 0) {
				game_start = 1;
				glutIdleFunc(move);
			}
		}

	} else if(key == 'w') {
		backgroundColor(2);

	} else if(key == 'b') {
		backgroundColor(1);

	} else if(key == 'i') {
		backgroundColor(3);

	} else if(key == 'o') {
		backgroundColor(4);
	}
	glutPostRedisplay();
}

void mainMenu(GLint option) {
	switch (option) {
	case 1: { //reset
		reset();
		break;
	}
	case 2: {
		exit(0);
	}
		break;
	case 3: {
		game_start = 1;
		glutIdleFunc(move);

		break;
	}
	case 4: {
		new_game();
	}
	}

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

void glslMenu(GLint x) {
	switch(x) {
	case 1:
		glUseProgram(programObject);
		break;
	case 2:
		glUseProgram(0);
	}
}

void backgroundColor(GLint x) {
	switch (x) {
	case 1: //Black
		myWorld.list[2]->textureID = 1; //left wall
		myWorld.list[3]->textureID = 3; //top wall
		myWorld.list[4]->textureID = 3; //right wall
		myWorld.list[5]->textureID = 3; //bottom wall
		whiteBackground = false;
		break;
	case 2: //white
		myWorld.list[2]->textureID = 0; //left wall
		myWorld.list[3]->textureID = 2; //top wall
		myWorld.list[4]->textureID = 2; //right wall
		myWorld.list[5]->textureID = 2; //bottom wall
		whiteBackground = true;
		break;

	case 3: //inverted 1
		myWorld.list[2]->textureID = 0; //left wall
		myWorld.list[3]->textureID = 2; //top wall
		myWorld.list[4]->textureID = 3; //right wall
		myWorld.list[5]->textureID = 3; //bottom wall
		break;
	case 4: //inverted 2
		myWorld.list[2]->textureID = 1; //left wall
		myWorld.list[3]->textureID = 3; //top wall
		myWorld.list[4]->textureID = 2; //right wall
		myWorld.list[5]->textureID = 2; //bottom wall
	}
	glutPostRedisplay();
}

void menu() {
	GLint Print_Menu, Background_Color, GLSL_Menu;

	GLSL_Menu = glutCreateMenu(glslMenu);
	glutAddMenuEntry( " On ", 1);
	glutAddMenuEntry( " Off ", 2);


	Print_Menu = glutCreateMenu(printMenu);
	glutAddMenuEntry(" Print View Variables ", 1);

	Background_Color = glutCreateMenu(backgroundColor);
	glutAddMenuEntry(" Black ", 1);
	glutAddMenuEntry(" White ", 2);
	glutAddMenuEntry(" Inverted 1 ", 3);
	glutAddMenuEntry(" Inverted 2 ", 4);

	glutCreateMenu(mainMenu);      // Create main pop-up menu.

	glutAddMenuEntry(" New Game ", 4);
	glutAddSubMenu( " Background ", Background_Color);
	glutAddMenuEntry(" Reset ", 1);
	glutAddMenuEntry(" Game Start/Stop ", 3);
	glutAddSubMenu(" GLSL ", GLSL_Menu);
	glutAddMenuEntry(" Quit", 2);
}

/*-------MENUS END------------------------------------------------------------*/

/*----MAIN---------------------------*/
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("CP411 Final Project: CurveBall 2.0");
	glewInit();
	init();
	menu();

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(keyPressed);
	glutMainLoop();

	return 0;
}

