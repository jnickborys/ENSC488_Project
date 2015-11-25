// Elnaz Implemented Source code
#include "stdafx.h"//PreCompiled Library
#include<stdio.h> // Standard Input and Output Library
#include "elnaz.h"
#include<math.h> // Math Functions Library
#include<windows.h> // Windows API library
#include<GL/gl.h> // OpenGL Library
#include<GL/glut.h> // GLUT Library
#include "GL/glui.h" // Including the glui libraries (if needed)

// Menue selection declarations
#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4
#define PI 3.1415926535 // Value of pi

struct Rotation	//Struct that passes values to change various Orientations of the articulated Joints
{
	float angle;
	float xAxis;
	float yAxis;
	float zAxis;
};

GLUquadric *quad;

//Using two Longer Cubes and a Joint to Show a full Arm
void drawarm ()
{
	glPushMatrix();

	glPushMatrix();
		glColor3f(1,0.5,0.5);
		glTranslatef (0,0,0);
		glutSolidSphere (1,50,50); 
	glPopMatrix();

	glPushMatrix();
		glTranslatef (0,-7,0);
		glColor3f(0.5,1,0.5);
		glScalef(1.6,12,1.6);
		glutSolidCube(1);
	glPopMatrix ();

	glPushMatrix();
		glColor3f(1,0.5,0.5);
		glTranslatef (0,-14,0);
		glutSolidSphere (1,50,50); 
	glPopMatrix ();

	glPushMatrix();
		glTranslatef (0,-21,0);
		glColor3f(0.5,1,0.5);
		glScalef(1.6,12,1.6);
		glutSolidCube(1);
	glPopMatrix ();

	glPushMatrix();
		glTranslatef (0,7,0);
		glColor3f(0.5,1,0.5);
		glScalef(1.6,12,1.6);
		glutSolidCube(1);
	glPopMatrix ();


	glPopMatrix ();

	
}


//Function Definition to Draw Cubes
void drawcube ()
{ 
glEnable(GL_DEPTH_TEST);
glBegin(GL_QUADS);
glColor3f(1.0,0.0,1.0); //Purple
// front
glVertex3f(0.0f,0.0f,0.0f);
glVertex3f(1.0f,0.0f,0.0f);
glVertex3f(1.0f,1.0f,0.0f);
glVertex3f(0.0f,1.0f,0.0f);

glColor3f(0.0,1.0,0.0); //Green
//back
glVertex3f(0.0f,0.0f,-1.0f);
glVertex3f(1.0f,0.0f,-1.0f);
glVertex3f(1.0f,1.0f,-1.0f);
glVertex3f(0.0f,1.0f,-1.0f);

glColor3f(0.0,0.0,1.0);  // Blue
//right
glVertex3f(1.0f,0.0f,0.0f);
glVertex3f(1.0f,0.0f,-1.0f);
glVertex3f(1.0f,1.0f,-1.0f);
glVertex3f(1,1.0f,0.0f);

glColor3f(0,1,1.0);		//cyan
//left
glVertex3f(0.0f,0.0f,0.0f);
glVertex3f(0.0f,0.0f,-1.0f);
glVertex3f(0.0f,1.0f,-1.0f);
glVertex3f(0,1.0f,0.0f);

glColor3f(0.0,0.5,0.0);  //Dark Green
//top
glVertex3f(0.0f,1.0f,0.0f);
glVertex3f(1.0f,1.0f,0.0f);
glVertex3f(1.0f,1.0f,-1.0f);
glVertex3f(0,1.0f,-1.0f);

glColor3f(0.5,0,1.0);  //Dark Purple
//bottom
glVertex3f(0.0f,0.0f,0.0f);
glVertex3f(1.0f,0.0f,0.0f);
glVertex3f(1.0f,0.0f,-1.0f);
glVertex3f(0,0.0f,-1.0f);

glEnd();
glDisable (GL_DEPTH_TEST);

}

