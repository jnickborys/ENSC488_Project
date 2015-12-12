// Utitlity Functions
// Contains Functions for useful drawing routines and controls

#include "stdafx.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include "global_constants.h"
#include "UserInterface.h"
#include "stateInformation.h"
#include "drawFunctions.h"
#include "elnaz.h"
#include "jim.h"
#include "Camera.h"
#include "utils_488.h"

void drawCamera(const GLfloat eye[], const GLfloat focus[], const GLfloat rotc[], const GLint draw_rot);

//float RotationDeg = 0;  // should make a dynamic value that change rotation.
float DistFromOrigin = 2;

GLfloat WristLinkParams[][4] = { { 0,1,0,0 },
								{ 0,1,0,0 },
								{ 0,0,0,DistFromOrigin },
								{ 0,0,0,-DistFromOrigin } };

//GLfloat _Oldeye[] = { 10, 10, 10};
//GLfloat _Oldfocus[] = { 0, 10, 0 };
//GLfloat _Oldrotc[] = { 0, 0 };

Camera camera = Camera();

void reshapeEventHandler(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, GLfloat(w) / GLfloat(h), 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
}

void mouseEventHandler(int button, int state, int x, int y)
{
	return;
}

float computeTheta23(const float K, const float theta1, const float theta3)
{
	float a3 = forwardKinParam[1][3];
	float a2 = forwardKinParam[2][3];

	float d4 = forwardKinParam[3][1];

	float s1 = sin(theta1);
	float c1 = cos(theta1);
	float s3 = sin(theta3);
	float c3 = cos(theta3);
	float px = inverseKinParam[0];
	float py = inverseKinParam[1];
	float pz = inverseKinParam[2];
	float theta23 = 0;

	float temp1 = (-a3 - a2*c3) * pz - (c1 * px + s1*py)*(d4 - a2*s3);
	float temp2 = (a2*s3 - d4) * pz - (a3 + a2*c3)*(c1*px + s1*py);
	theta23 = atan2f(temp1, temp2);
	return theta23;
}

void ComputeInvKin()
{
	float currentFrame[16] = { 0 };
	float d4 = 0;
	float d3 = 0;
	float theta1a = 0;
	float theta1b = 0;

	float theta2[4] = { 0 };
	float theta3a = 0;
	float theta3b = 0;

	float theta23[4] = { 0 };
	enum {aa, ba, ab, bb};

	float px, py, pz;

	float a2 = 1;
	float a3 = 1;

	float K = 0;

	//D_val = linkFrameParam[link][3];
	d3 = 0;

	px = inverseKinParam[0];
	py = inverseKinParam[1];
	pz = inverseKinParam[2];

	float rho_p = sqrtf(px*px + py*py - d3*d3);
	float rho_n = -sqrtf(px*px + py*py - d3*d3);
	
	float phi = atan2f(py, px);

	float theta_v1 = atan2f(d3, rho_p);
	float theta_v2 = atan2f(d3, rho_n);

	theta1a = (phi - theta_v1) * 1 / DEGREES_TO_RAD;
	theta1b = (phi - theta_v2) * 1 / DEGREES_TO_RAD;

	float temp1 = sqrt(a3*a3 + d4*d4 - K*K);
	float temp2 = -sqrt(a3*a3 + d4*d4 - K*K);

	K = (px*px + py*py + pz*pz - a2*a3 - a3*a3 - d3*d3 - d4*d4) / (2*a2);

	theta3a = atan2f(a3, d4) - atan2f(K, temp1);
	theta3b = atan2f(a3, d4) - atan2f(K, temp2);
	
	theta23[aa] = computeTheta23(K, theta1a, theta3a);
	theta23[ba] = computeTheta23(K, theta1b, theta3a);
	theta23[ab] = computeTheta23(K, theta1a, theta3b);
	theta23[bb] = computeTheta23(K, theta1b, theta3b);
	
	theta2[aa] = (theta23[aa] - theta3a) * 1 / DEGREES_TO_RAD;
	theta2[ba] = (theta23[ba] - theta3a) * 1 / DEGREES_TO_RAD;
	theta2[ab] = (theta23[ab] - theta3a) * 1 / DEGREES_TO_RAD;
	theta2[bb] = (theta23[bb] - theta3a) * 1 / DEGREES_TO_RAD;

	theta3a = theta3a * 1 / DEGREES_TO_RAD;
	theta3b = theta3b * 1 / DEGREES_TO_RAD;

	forwardKinParam[1][2] = theta1a;
	forwardKinParam[2][2] = theta2[aa];
	forwardKinParam[3][2] = theta3a;

	return;
}

float sgn(float x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

float getTheta()
{
	float theta = 0;
	theta = atan2f(inverseKinParam[2], inverseKinParam[0]);
	if (inverseKinParam[0] < 0) // Quadrants 1 and 4
	{
		float sign = sgn(theta);
		theta = theta + sign * PI/2.0;
	}
	return theta/DEGREES_TO_RAD;
}

void renderScene(void)
{

	glDepthMask(GL_TRUE);
	glClearColor(0.4f, 0.4f, 0.95, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// After the draw Camera call the world is no longer referenced 
	// with respect to the identity matrix. Might be a good idea to push
	// this matrix onto the stack

	camera.Update();

	if (ENABLE_INV_KIN){
		forwardKinParam[0][0] = getTheta() + 180;
		//ComputeInvKin();
	}

	// To make the Code more separated I am including some functions to 
	// break out our code this way all changes can be done in the specific 
	// draw functions
	
	drawJeremy();
	
	glRotatef(-90, 1, 0, 0);

	glPushMatrix();
	glTranslatef(1, 1, 1);
	glutSolidSphere(.1, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 1, 0);
	glutSolidSphere(.1, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 0, 1);
	glutSolidSphere(.1, 12, 12);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 1, 1);
	glutSolidSphere(.1, 12, 12);
	glPopMatrix();

	glPushMatrix();
		drawElnaz(forwardKinParam);

		glRotatef(-90, 0, 1, 0);
		glScalef(0.1, 0.1, 0.1);
		drawJim(WristLinkParams);
	glPopMatrix();
	////drawFloor(100, 100, -1);

	computeStaticBalanceTorque();

	glutSwapBuffers();
	return;
}

void test_static_balance_torque(GLfloat f2[])
{
	GLfloat p1[] = { 0, 0, 0, 0 };
	GLfloat p2[] = { 0, 0, 0, 0 };
	GLfloat p3[] = { 0, 0, 0, 0 };

	GLfloat t1 = 0;
	GLfloat t2 = 0;

	GLfloat theta2 = 45;
	GLfloat l1 = 1;
	GLfloat l2 = 1;

	GLfloat s2 = sin(theta2 * DEGREES_TO_RAD);
	GLfloat c2 = cos(theta2 * DEGREES_TO_RAD);

	t1 = (l1 * s2 * f2[0]) + f2[1]*(l2 + l1*c2);
	t2 = l2 * f2[1];

}

void keyBoardEventHandler(unsigned char key, int x, int y)
{

	/* 
	WASD does not work as described yet and only increment the eyepostion
	Camera move really needs to increment the separation vector in the 
	Desired direction not some camera Eye position
	*/
	const static float forward[] = { 1, 0, 0 };
	const static float backward[] = { -1, 0, 0 };
	const static float left[] = { 0, 0, -1 };
	const static float right[] = { 0, 0, 1 };

	switch (key) {
	case 'w':
		camera.Move(forward);
		break;
	case 's':
		camera.Move(backward);
		break;
	case 'a':
		camera.Move(left);
		break;
	case 'd':
		camera.Move(right);
		break;
	case 'o':
		WristLinkParams[1][2] += 10;
		break;
	case 'p':
		WristLinkParams[1][2] -= 10;
		break;

	case 'k':
		WristLinkParams[2][3] += 0.2;
		WristLinkParams[3][3] -= 0.2;

		//Limit the open position
		if (WristLinkParams[2][3] >= 2) {
			WristLinkParams[2][3] = 2;
			WristLinkParams[3][3] = -2;
		}
		break;
	case 'l':
	
		WristLinkParams[2][3] -= 0.2;
		WristLinkParams[3][3] += 0.2;
		
		//Limit the close position
		if (WristLinkParams[2][3] <= 0) {
			WristLinkParams[2][3] = 0;
			WristLinkParams[3][3] = 0;
		}

		break;
	case 'm':
		forwardKinParam[0][0]+=10;
		break;
	case 27: // "27" is theEscape key
		exit(1);
	}
	return;
}


void specialCharEventHandler(int key, int x, int y)
{
	/*
	WASD does not work as described yet and only increment the eyepostion
	Camera move really needs to increment the separation vector in the
	Desired direction not some camera Eye position
	*/
	const static float up[] = { 0, 1, 0 };
	const static float down[] = { 0, -1, 0 };
	const static float left[] = { 0, 0, -1 };
	const static float right[] = { 0, 0, 1 };

	switch (key)
	{
	case GLUT_KEY_UP:
		camera.Rotate(up);
		break;
	case GLUT_KEY_DOWN:
		camera.Rotate(down);
		break;
	case GLUT_KEY_LEFT:
		camera.Rotate(left);
		break;
	case GLUT_KEY_RIGHT:
		camera.Rotate(right);
		break;
	default:
		break;
	}
	return;
}


void cross3(const GLfloat a[], const GLfloat b[], GLfloat s[])
{
	s[0] = (a[1] * b[2]) - (a[2] * b[1]);
	s[1] = (a[2] * b[0]) - (a[0] * b[2]);
	s[2] = (a[0] * b[1]) - (a[1] * b[0]);
	return;
}

void getSeparationVector(const GLfloat v1[], const GLfloat v2[], GLfloat r[])
{
	r[0] = v2[0] - v1[0];
	r[1] = v2[1] - v1[1];
	r[2] = v2[2] - v1[2];
	return;
}

GLfloat magnitude(const GLfloat *vec, int size)
{
	GLfloat result = 0;
	for (int i = 0; i < size; ++i)
	{
		result += vec[i] * vec[i];
	}
	return sqrtf(result);
}

/* 
	Legacy Camera Function No longer used, Now I am going to use the camera 
	class to determine the movements.
*/
//Rotate the Camera along the Y Axis and Pitch Axis
void drawCamera(const GLfloat eye[], const GLfloat focus[], const GLfloat rotc[], const GLint draw_rot)
{
	GLfloat crossEyexUY[] = { 0, 0, 0 }; // Cross product of the Eye position and Unit Y vector
	GLfloat posv[] = { 0, 0, 0 };

	GLfloat uy[] = { 0, 1, 0 };
	GLfloat mag = 0;

	// Get the cross product of the Eye position and the y axis
	getSeparationVector(eye, focus, posv);
	cross3(posv, uy, crossEyexUY);
	mag = magnitude(crossEyexUY, 3);

	gluLookAt(eye[0], eye[1], eye[2], focus[0], focus[1], focus[2], 0.0, 1.0, 0.0);

	if (draw_rot) {
		glPushMatrix();
		glTranslatef(focus[0], focus[1], focus[2]);
		glColor3f(1, 0.5, 0);
		// draw normal vector from unit y and camera
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(crossEyexUY[0] / mag, crossEyexUY[1] / mag, crossEyexUY[2] / mag);
		glEnd();

		glColor3f(0, 0.5, 1);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glEnd();
		glPopMatrix();
	}

	// perform rotations necessary to move the world relative to the camera
	glRotatef(rotc[0], crossEyexUY[0], crossEyexUY[1], crossEyexUY[2]);
	glRotatef(rotc[1], 0, 1, 0);
}

/*
delta_frame ( alpha,a,theta,d)
	Draws a position using a delta_frame which is a difference between two reference frames A and B.

	delta_frame is of size 4and has the parameters:
		alpha:	angle (in deg) to rotate around z axis to bring the frame to x' 
		a:		offset (in meters) from x' axis to the new Position in frame 2
		theta:  angle (in deg) to align z' axis to the new z'' axis in frame 2
		d:		offset (in deg) move the newly aligned position
*/
void frame2frame(const GLfloat delta_frame[], GLint enable_vertice_axis, GLint no_line) {

	enum positions {alpha, a, theta, d};

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(0, 0.0, 0);
	glEnd();
	glPointSize(1);

	if (enable_vertice_axis)
		drawAxis(0.5);

	glRotatef(delta_frame[alpha], 0, 0, 1);

	if (enable_vertice_axis)
		drawAxis(0.1);

	if (!no_line)
	{
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(delta_frame[a], 0, 0);
		glEnd();
	}

	glTranslatef(delta_frame[a], 0, 0);
	//glRotatef(delta_frame[alpha], 0, 0, 1);

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex3f(0, 0.0, 0);
	glEnd();
	glPointSize(1);

	glRotatef(delta_frame[theta], 1, 0, 0);

	if (!no_line)
	{
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, delta_frame[d]);
		glEnd();
	}
	glTranslatef(0, 0, delta_frame[d]);
	
	if (enable_vertice_axis)
		drawAxis(0.5);

	glPointSize(5);
		glBegin(GL_POINTS);
		glVertex3f(0, 0.0, 0);
		glEnd();
	glPointSize(1);

	if (enable_vertice_axis)
		drawAxis(0.1);
}


