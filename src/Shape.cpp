/**
 * 	Shape.cpp
 *	CP411 Assignment 2
 *	Robin Sharma
 *	ID: 110142530
 *	Email: shar2530@mylaurier.ca
 *	Date: October 18, 2013
 */

#include "Shape.hpp"

Shape::Shape() {
	MC.mat[0][0] = 1.0;
	MC.mat[0][1] = 0.0;
	MC.mat[0][2] = 0.0;
	MC.mat[0][3] = 0.0;
	MC.mat[1][0] = 0.0;
	MC.mat[1][1] = 1.0;
	MC.mat[1][2] = 0.0;
	MC.mat[1][3] = 0.0;
	MC.mat[2][0] = 0.0;
	MC.mat[2][1] = 0.0;
	MC.mat[2][2] = 1.0;
	MC.mat[2][3] = 0.0;
	MC.mat[3][0] = 0.0;
	MC.mat[3][1] = 0.0;
	MC.mat[3][2] = 0.0;
	MC.mat[3][3] = 1.0;
	sx = 1;
	sy = 1;
	sz = 1;
}

Shape::~Shape() {
}
;

Matrix Shape::getMC() {
	return MC;
}
;

void Shape::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	MC.translate(tx, ty, tz);
	MC.normalize();
}

void Shape::rotate(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	MC.rotate(rx, ry, rz, angle);
	MC.normalize();
}

void Shape::rotate_mc(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	GLfloat x0, y0, z0;
	x0 = MC.mat[0][3];
	y0 = MC.mat[1][3];
	z0 = MC.mat[2][3];

	MC.rotate(rx, ry, rz, angle);
	MC.mat[0][3] = x0;
	MC.mat[1][3] = y0;
	MC.mat[2][3] = z0;

	MC.normalize();
}

void Shape::rotate_origin(GLfloat rx, GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix* m = new Matrix();
	m->rotate(rx, ry, rz, angle);
	GLfloat v[4];
	v[0] = MC.mat[0][3];
	v[1] = MC.mat[1][3];
	v[2] = MC.mat[2][3];
	v[3] = MC.mat[3][3];
	m->multiply_vector(v);
	MC.mat[0][3] = v[0];
	MC.mat[1][3] = v[1];
	MC.mat[2][3] = v[2];
	MC.mat[3][3] = v[3];
	delete m;
	MC.normalize();
}

void Shape::rotate_relative(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat rx,
		GLfloat ry, GLfloat rz, GLfloat angle) {
	Matrix* m = new Matrix();
	m->rotate(rx, ry, rz, angle * 1);
	GLfloat v[4];
	v[0] = MC.mat[0][3] - x0;
	v[1] = MC.mat[1][3] - y0;
	v[2] = MC.mat[2][3] - z0;
	v[3] = MC.mat[3][3] - 1;

	m->multiply_vector(v);
	// MC.matrix_pre_multiply(m);
	MC.mat[0][3] = v[0] + x0;
	MC.mat[1][3] = v[1] + y0;
	MC.mat[2][3] = v[2] + z0;
	MC.mat[3][3] = v[3] + 1;

	delete m;

}

void Shape::scale_change(GLfloat x) {
	scaleX(x);
	scaleY(x);
	scaleZ(x);
	MC.normalize();
}

void Shape::scaleX(GLfloat x) {
	if (sx > 0) {
		sx += x;
		MC.normalize();
	}
}

void Shape::scaleY(GLfloat y) {
	if (sy > 0) {
		sy += y;
		MC.normalize();
	}
}

void Shape::scaleZ(GLfloat z) {
	if (sz > 0) {
		sz += z;
		MC.normalize();
	}
}

/**
 * Shape::ctm_multiply() multiply this matrix to openGL current matrix
 */
void Shape::ctm_multiply() {
	GLfloat M[16];
	M[0] = MC.mat[0][0];
	M[1] = MC.mat[1][0];
	M[2] = MC.mat[2][0];
	M[3] = 0;
	M[4] = MC.mat[0][1];
	M[5] = MC.mat[1][1];
	M[6] = MC.mat[2][1];
	M[7] = 0;
	M[8] = MC.mat[0][2];
	M[9] = MC.mat[1][2];
	M[10] = MC.mat[2][2];
	M[11] = 0;
	M[12] = MC.mat[0][3];
	M[13] = MC.mat[1][3];
	M[14] = MC.mat[2][3];
	M[15] = 1;
	glMultMatrixf(M);
}

