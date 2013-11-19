#include "Camera.hpp"

//This has all the information for the camera
Camera::Camera() {
	xeye = 3.0, yeye = 3.0, zeye = 7.0;  //  Viewing-coordinate origin.
	xref = 0.0, yref = 0.0, zref = 0.0;  //  Look-at point.
	Vx = 0.0, Vy = 1.0, Vz = 0.0;        //  View up vector.
	stereo = 0; //0 for Mono, 1 for Stereo
	/*  Set coordinate limits for the clipping window:  */
	xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

	/*  Set positions for near and far clipping planes:  */
	vangle = 40.0, dnear = 2.0, dfar = 15.0;
}


//This function rotates the VC system
void Camera::rotate_view(double x, double y, double z, double angle) {
	Matrix* m = new Matrix();
	m->rotate(x, y, z, angle);

	GLfloat v[4];
	v[0] = xeye;
	v[1] = yeye;
	v[2] = zeye;
	v[3] = 0;

	m->multiply_vector(v);

	xeye = v[0];
	yeye = v[1];
	zeye = v[2];

	delete m;
}

//This function translates the VC system
void Camera::translate_view(double x, double y, double z) {
	xeye = xeye + x;
	yeye = yeye + y;
	zeye = zeye + z;
}

//This function changes the viewing angle of the VC system
void Camera::change_view_angle(double angle) {
	vangle = vangle + angle;
}

// This function changes the dnear value for the front clipping
void Camera::change_dnear(double change) {
	if (dnear < dfar && change > 0)
		dnear = dnear + change;
	else if (dnear > 0 && change < 0)
		dnear = dnear + change;
}

//This function changes the dfar value for rear clipping
void Camera::change_dfar(double change) {
	if (dfar > dnear && change < 0)
		dfar = dfar + change;
	else if (change > 0)
		dfar = dfar + change;
}

