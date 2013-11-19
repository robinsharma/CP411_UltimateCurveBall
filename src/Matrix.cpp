/**
 * 	Matrix.cpp
 *	CP411 Assignment 2
 *	Robin Sharma
 *	ID: 110142530
 *	Email: shar2530@mylaurier.ca
 *	Date: October 18, 2013
 */

#include "Matrix.hpp"

// construct an identity matrix as mat
Matrix::Matrix() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				this->mat[i][j] = 1;
			else
				this->mat[i][j] = 0;
		}
	}
}

// multiplication  mat <- m * mat
void Matrix::matrix_pre_multiply(Matrix* m) {
	Matrix* temp = new Matrix();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GLfloat sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += m->mat[i][k] * this->mat[k][j];
			}
			temp->mat[i][j] = sum;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			this->mat[i][j] = temp->mat[i][j];
		}
	}
	delete temp;
}

// translate the origin of MC
void Matrix::translate(GLfloat tx, GLfloat ty, GLfloat tz) {
	this->mat[0][3] += tx;
	this->mat[1][3] += ty;
	this->mat[2][3] += tz;
	this->mat[3][3] = 1;
}

void Matrix::transpose() {
}
// normalize MC
void Matrix::normalize() {
	GLfloat norm;

	norm = sqrt(
			mat[0][0] * mat[0][0] + mat[1][0] * mat[1][0]
					+ mat[2][0] * mat[2][0]);

	this->mat[0][0] = mat[0][0] / norm;
	this->mat[1][0] = mat[1][0] / norm;
	this->mat[2][0] = mat[2][0] / norm;

	this->mat[0][2] = mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1];
	this->mat[1][2] = mat[2][0] * mat[0][1] - mat[0][0] * mat[2][1];
	this->mat[2][2] = mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];

	norm = sqrt(
			mat[0][2] * mat[0][2] + mat[1][2] * mat[1][2]
					+ mat[2][2] * mat[2][2]);

	this->mat[0][2] = mat[0][2] / norm;
	this->mat[1][2] = mat[1][2] / norm;
	this->mat[2][2] = mat[2][2] / norm;

	this->mat[0][1] = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2];
	this->mat[1][1] = mat[2][2] * mat[0][0] - mat[2][0] * mat[0][2];
	this->mat[2][1] = mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2];

	this->mat[3][0] = 0;
	this->mat[3][1] = 0;
	this->mat[3][2] = 0;
	this->mat[3][3] = 1;
}

// v  <- mat * v
void Matrix::multiply_vector(GLfloat* v) {
	double sum, temp[4];
	for (int i = 0; i < 4; i++) {
		sum = 0;
		for (int j = 0; j < 4; j++) {
			sum += v[j] * this->mat[i][j];
		}
		temp[i] = sum;
	}
	for (int i = 0; i < 4; i++) {
		v[i] = temp[i];
	}
}

// MC <= rotation matrix * MC, i.e., rotate coordinate vectors and the origin
void Matrix::rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat angle) {
	normalize();
	angle = angle * 3.1415926 / 180;
	float oneC = 1 - cos(angle);
	float COS = cos(angle);
	float SIN = sin(angle);

	Matrix* m = new Matrix();

	m->mat[0][0] = x * x * oneC + cos(angle);
	m->mat[0][1] = y * x * oneC + z * sin(angle);
	m->mat[0][2] = x * z * oneC - y * SIN;
	m->mat[0][3] = 0;
	m->mat[1][0] = x * y * oneC - z * SIN;
	m->mat[1][1] = y * y * oneC + COS;
	m->mat[1][2] = y * z * oneC + x * SIN;
	m->mat[1][3] = 0;
	m->mat[2][0] = x * z * oneC + y * SIN;
	m->mat[2][1] = y * z * oneC - x * SIN;
	m->mat[2][2] = z * z * oneC + COS;
	m->mat[2][3] = 0;
	m->mat[3][0] = 0;
	m->mat[3][1] = 0;
	m->mat[3][2] = 0;
	m->mat[3][3] = 1;

	this->matrix_pre_multiply(m);
	delete m;
	normalize();

}

