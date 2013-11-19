#ifndef CCAMERA_H
#define CCAMERA_H

#include <GL/glut.h>
#include "Shape.hpp"

class Camera {
protected:

public:

	Camera();
	void rotate_view(double, double, double, double);
	void translate_view(double, double, double);
	void change_view_angle(double);
	void change_dnear(double);
	void change_dfar(double);
	void CameraHome(int);

	GLfloat xeye, yeye, zeye;  //  Viewing-coordinate origin.
	GLfloat xref, yref, zref;  //  Look-at point.
	GLfloat Vx, Vy, Vz;        //  View up vector.
	GLint stereo; //0 for Mono, 1 for Stereo
	/*  Set coordinate limits for the clipping window:  */
	GLfloat xwMin, ywMin, xwMax, ywMax;
	/*  Set positions for near and far clipping planes:  */
	GLfloat vangle, dnear, dfar;


};

#endif
