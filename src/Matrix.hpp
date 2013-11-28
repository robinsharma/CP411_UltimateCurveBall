/**
 * 	Matrix.hpp
 */

#ifndef CMATRIX_H
#define CMATRIX_H

#include <iostream>
#include <GL/gl.h>
#include <math.h>

using namespace std;

class Matrix {
public:
	GLfloat mat[4][4];   	// this matrix is for MC
	Matrix();  				// constructor
	void matrix_pre_multiply(Matrix* m);  	// m*mat
	void transpose();  						// mat'
	void translate(GLfloat x, GLfloat y, GLfloat z);  // translate MC =  T(x, y, z)
	void rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle); //rotate w.r.p.t. vector (x, y, z) by angle
	void multiply_vector(GLfloat* v); // mat*v
	void normalize();  // this function is to normalize MC
};

#endif
