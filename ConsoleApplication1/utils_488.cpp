// Utitlity Functions
// Contains Functions for useful drawing routines and controls

#include "stdafx.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include "drawFunctions.h"
#include "elnaz.h"
#include "jim.h"
#include "Camera.h"

void drawCamera(const GLfloat eye[], const GLfloat focus[], const GLfloat rotc[], const GLint draw_rot);

	int alpha1=0;
	int alpha2=0;
	int alpha3=0;
	int alpha4=0;
	int theta1=0;
	int d1=1;
	int d2=1;
	int d3=1;
	int d4=1;

GLfloat jointParam[][4]={{theta1,0,alpha1,0}, 
							 {0,0,alpha2,d1},
							 {0,0,alpha3,d2},
							 {0,0,alpha4,d3}};

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

	

	// To make the Code more separated I am including some functions to 
	// break out our code this way all changes can be done in the specific 
	// draw functions

	drawElnaz(jointParam);


	//drawJeremy();
	
	//drawJim();

	//drawFloor(100, 100, -1);

	glutSwapBuffers();
	return;
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
	case 'm':
		jointParam[0][0]+=10;
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
		drawAxis(0.1);

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
		drawAxis(0.1);

	glPointSize(5);
		glBegin(GL_POINTS);
		glVertex3f(0, 0.0, 0);
		glEnd();
	glPointSize(1);

	if (enable_vertice_axis)
		drawAxis(0.1);
}



