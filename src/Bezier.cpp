/*
 * Bezier.cpp
 *
 *  Created on: Nov 12, 2013
 *      Author: Robin
 */

#include "Bezier.hpp"
#include <stdio.h>

//extern wcPt3D ctrlPts[10]; // to store control points,
//extern wcPt3D RBM[73][26], RBC_face_norm[73][26]; // to store the mesh points and norm at each points

extern GLint R, S, T, Ptgen, BCgen, BCRotation;
extern GLfloat red, green, blue;

extern GLint style;
extern GLint winWidth, winHeight;

#define Pi 3.141592653589793238462643

Bezier::Bezier() {
	nCtrlPts = 0; // number control points selected
	R = 45, S = 5, T = 5; // Rotation variables
	Ptgen = 1, BCgen = 0, BCRotation = 0; // state variables for control point generation, Bezier curve generation, Bezier curve rotation
	red = 1.0, green = 0.0, blue = 0.0;
}

void Bezier::draw2DFrame() {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-winWidth / 4, 0.0);
	glVertex2f(winWidth / 4, 0.0);

	glColor3f(0.0, 1.0, 0.0);

	glVertex2f(0.0, -winHeight / 4);
	glVertex2f(0.0, winHeight / 4);
	glEnd();
}

void Bezier::setPixel(GLfloat x, GLfloat y) {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

/* Compute binomial coefficients C for given value of n. */
void Bezier::binomialCoeffs(GLint n, GLint * C) {
	GLint k, j;
	for (k = 0; k <= n; k++) {
		/* Compute n!/(k!(n - k)!). */
		C[k] = 1;
		for (j = n; j >= k + 1; j--)
			C[k] *= j;
		for (j = n - k; j >= 2; j--)
			C[k] /= j;
	}
}

void Bezier::computeBezPt(GLfloat u, wcPt3D * bezPt, wcPt3D * BezTan,
		GLint nCtrlPts, wcPt3D * ctrlPts, GLint * C) {
	GLint k, n = nCtrlPts - 1;
	GLfloat bezBlendFcn, factor = 1.0;

	bezPt->x = bezPt->y = bezPt->z = 0.0;
	BezTan->x = BezTan->y = BezTan->z = 0.0;

	/* Compute blending functions and blend control points. */
	for (k = 0; k < nCtrlPts; k++) {
		bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);

		bezPt->x += ctrlPts[k].x * bezBlendFcn;
		bezPt->y += ctrlPts[k].y * bezBlendFcn;
		bezPt->z += ctrlPts[k].z * bezBlendFcn;

		if (u < 0.001) {
			BezTan->x = ctrlPts[1].x - ctrlPts[0].x;
			BezTan->y = ctrlPts[1].y - ctrlPts[0].y;
			BezTan->z = ctrlPts[1].z - ctrlPts[0].z;
		} else if (1 - u < 0.001) {
			BezTan->x = ctrlPts[n + 1].x - ctrlPts[n].x;
			BezTan->y = ctrlPts[n + 1].y - ctrlPts[n].y;
			BezTan->z = ctrlPts[n + 1].z - ctrlPts[n].z;
		} else {
			factor = k / u - (n - k) / (1 - u);
			BezTan->x += ctrlPts[k].x * bezBlendFcn * factor;
			BezTan->y += ctrlPts[k].y * bezBlendFcn * factor;
			BezTan->z += ctrlPts[k].z * bezBlendFcn * factor;
		}
	}
}

// draw bezier curve
void Bezier::bezier(wcPt3D * ctrlPts, GLint nCtrlPts, GLint nBezCurvePts) {
	wcPt3D bezCurvePt, bezCurveTangent;
	GLfloat u;
	GLint *C, k;
	/* Allocate space for binomial coefficients */
	C = new GLint[nCtrlPts];
	binomialCoeffs(nCtrlPts - 1, C);
	for (k = 0; k <= nBezCurvePts; k++) {
		u = GLfloat(k) / GLfloat(nBezCurvePts);
		computeBezPt(u, &bezCurvePt, &bezCurveTangent, nCtrlPts, ctrlPts, C);
		setPixel(bezCurvePt.x, bezCurvePt.y);
	}
	delete[] C;
}

// generate the mesh point of rotation point
void Bezier::RotateBezier(wcPt3D * ctrlPts, GLint nCtrlPts,
		GLint nBezCurvePts) {
	wcPt3D bezCurvePt, bezCurveTangent;
	GLfloat u;
	GLint *C, k, i;
	GLfloat x, y, temp;

	/* Allocate space for binomial coefficients */
	C = new GLint[nCtrlPts];

	binomialCoeffs(nCtrlPts - 1, C);

	for (k = 0; k <= T; k++) {
		u = GLfloat(k) / GLfloat(T);
		computeBezPt(u, &bezCurvePt, &bezCurveTangent, nCtrlPts, ctrlPts, C);

// generate mesh point of on the rotation circle.
		for (i = 0; i <= R / S; i++) {
			RBM[i][k].x = bezCurvePt.x;
			RBM[i][k].y = bezCurvePt.y * cos((Pi / 180) * S * i);
			RBM[i][k].z = bezCurvePt.y * sin((Pi / 180) * S * i);

// compute the normal at the each mesh point
			x = bezCurveTangent.x;
			y = bezCurveTangent.y;

			temp = x;
			x = -y;
			y = temp;

			RBC_face_norm[i][k].x = x;
			RBC_face_norm[i][k].y = y * cos((Pi / 180) * S * i);
			RBC_face_norm[i][k].z = y * sin((Pi / 180) * S * i);
		}
	}
	delete[] C;
}

void Bezier::drawWireRBC() {
	int i, j;
	glColor3f(red, green, blue);
	for (i = 0; i < int(R / S); i++) {
		for (j = 0; j < T; j++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(RBM[i][j].x, RBM[i][j].y, RBM[i][j].z);
			glVertex3f(RBM[i + 1][j].x, RBM[i + 1][j].y, RBM[i + 1][j].z);
			glVertex3f(RBM[i + 1][j + 1].x, RBM[i + 1][j + 1].y,
					RBM[i + 1][j + 1].z);
			glVertex3f(RBM[i][j + 1].x, RBM[i][j + 1].y, RBM[i][j + 1].z);
			glEnd();
		}
	}

	if (R == 360) {
		i = R / S - 1;

		for (j = 0; j < T; j++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(RBM[i][j].x, RBM[i][j].y, RBM[i][j].z);
			glVertex3f(RBM[0][j].x, RBM[0][j].y, RBM[0][j].z);
			glVertex3f(RBM[0][j + 1].x, RBM[0][j + 1].y, RBM[0][j + 1].z);
			glVertex3f(RBM[i][j + 1].x, RBM[i][j + 1].y, RBM[i][j + 1].z);
			glEnd();
		}
	}
}

void Bezier::drawSolidRBC() {
	int i, j;

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
	for (i = 0; i < R / S; i++) {
		for (j = 0; j < T; j++) {
			glBegin(GL_POLYGON);
			glColor3f(red, green, blue);
			glNormal3f(RBC_face_norm[i][j].x, RBC_face_norm[i][j].y,
					RBC_face_norm[i][j].z);
			glVertex3f(RBM[i][j].x, RBM[i][j].y, RBM[i][j].z);
			glVertex3f(RBM[i + 1][j].x, RBM[i + 1][j].y, RBM[i + 1][j].z);
			glVertex3f(RBM[i + 1][j + 1].x, RBM[i + 1][j + 1].y,
					RBM[i + 1][j + 1].z);
			glVertex3f(RBM[i][j + 1].x, RBM[i][j + 1].y, RBM[i][j + 1].z);
			glEnd();
		}

		for (j = 0; j < T; j++) {
			glBegin(GL_POLYGON);
			glColor3f(red, green, blue);
			glNormal3f(-RBC_face_norm[i][j].x, -RBC_face_norm[i][j].y,
					-RBC_face_norm[i][j].z);
			glVertex3f(RBM[i][j].x, RBM[i][j].y, RBM[i][j].z);
			glVertex3f(RBM[i][j + 1].x, RBM[i][j + 1].y, RBM[i][j + 1].z);
			glVertex3f(RBM[i + 1][j + 1].x, RBM[i + 1][j + 1].y,
					RBM[i + 1][j + 1].z);
			glVertex3f(RBM[i + 1][j].x, RBM[i + 1][j].y, RBM[i + 1][j].z);
			glEnd();
		}
	}
	if (R == 360) {
		i = R / S - 1;

		for (j = 0; j < T; j++) {
			glColor3f(red, green, blue);
			glNormal3f(RBC_face_norm[i][j].x, RBC_face_norm[i][j].y,
					RBC_face_norm[i][j].z);
			glBegin(GL_POLYGON);
			glVertex3f(RBM[i][j].x, RBM[i][j].y, RBM[i][j].z);
			glVertex3f(RBM[0][j].x, RBM[0][j].y, RBM[0][j].z);
			glVertex3f(RBM[0][j + 1].x, RBM[0][j + 1].y, RBM[0][j + 1].z);
			glVertex3f(RBM[i][j + 1].x, RBM[i][j + 1].y, RBM[i][j + 1].z);
			glEnd();

			glColor3f(red, green, blue);
			glNormal3f(-RBC_face_norm[i][j].x, -RBC_face_norm[i][j].y,
					-RBC_face_norm[i][j].z);
			glBegin(GL_POLYGON);
			glVertex3f(RBM[i][j].x, RBM[i][j].y, RBM[i][j].z);
			glVertex3f(RBM[0][j].x, RBM[0][j].y, RBM[0][j].z);
			glVertex3f(RBM[0][j + 1].x, RBM[0][j + 1].y, RBM[0][j + 1].z);
			glVertex3f(RBM[i][j + 1].x, RBM[i][j + 1].y, RBM[i][j + 1].z);
			glEnd();
		}
	}
}

void Bezier::displayCPts() {
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0); // Set display-window color to black
	draw2DFrame();
	drawCPts();
}

void Bezier::drawCPts() {
	glPointSize(3.0);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < nCtrlPts; i++) {
		setPixel(ctrlPts[i].x, ctrlPts[i].y);
	}
}

void Bezier::computeBezPt(GLfloat u, wcPt3D * bezPt, wcPt3D * BezTan,
		GLint nCtrlPts, wcPt3D * ctrlPts) {
// Given 0<u<1, the number of control points, and the list of control point list. Output the Bezier point at u, and the tangent vector at u.
}

void Bezier::drawBezCurve(wcPt3D * ctrlPts, GLint nCtrlPts) {
// Given the list of control points and the number of control points, draw the Bezier curve
// need to call computeBezPt to compute the points at u = 0, 1/100, 2/100, ..., 100/100
}

void Bezier::displayBezCurve() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
	draw2DFrame();
	displayCPts();

}

/*
void Bezier::drawRBC() {
// Given RBM[][], draw the frame of the rotation surface, or the filled polygon of each face
}
*/

void Bezier::draw() {
	glPushMatrix();
	this->ctm_multiply();
	glScalef(s * 0.01, s * 0.01, s * 0.01);
	if (Ptgen == 1) {
		displayBezCurve();
	}
	if (BCgen == 1) {
		displayBezCurve();
		bezier(ctrlPts, nCtrlPts, 1000);
	}
	if (BCRotation) {
		RotateBezier(ctrlPts, nCtrlPts, T);
		if (style == 1) {
			drawWireRBC();
		}
		if (style == 2) {
			drawSolidRBC();
		}
	}
	glPopMatrix();
}
