/*
 * Bezier.hpp
 *
 *  Created on: Nov 12, 2013
 *      Author: Robin
 */

#ifndef BEZIER_HPP_
#define BEZIER_HPP_

#include <GL/glut.h>
#include "Shape.hpp"
#include <math.h>
#include "wcPt3D.hpp"
class Bezier: public Shape {
public:

	wcPt3D ctrlPts[10]; // to store control points,
	wcPt3D RBM[73][26], RBC_face_norm[73][26]; // to store the mesh points and norm at each points
	GLint nCtrlPts;
	Bezier();
	void displayCPts();
	void setPixel(GLfloat, GLfloat);
	void binomialCoeffs(GLint, GLint *);

	void computeBezPt(GLfloat, wcPt3D *, wcPt3D *, GLint, wcPt3D *, GLint *);
	void bezier(wcPt3D *, GLint, GLint);
	void RotateBezier(wcPt3D * , GLint , GLint );
	void drawWireRBC();
	void drawSolidRBC();
	void draw2DFrame();
	void drawCPts();
	void computeBezPt(GLfloat, wcPt3D *, wcPt3D *,
			GLint, wcPt3D *);
	void drawBezCurve(wcPt3D *, GLint);
	void displayBezCurve();
	void drawRBC();
	void draw();
};

#endif /* BEZIER_HPP_ */
