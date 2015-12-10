// Elnaz Implemented Source code
#include "stdafx.h"//PreCompiled Library
#include<stdio.h> // Standard Input and Output Library
#include "elnaz.h"
#include<math.h> // Math Functions Library
#include<windows.h> // Windows API library
#include<GL/gl.h> // OpenGL Library
#include<GL/glut.h> // GLUT Library
#include "GL/glui.h" // Including the glui libraries (if needed)

#include "utils_488.h"
#include "drawFunctions.h"
#include "stateInformation.h"
#include "global_constants.h"

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

/*
	Elnaz insert all your drawing code in the function drawElnaz(). drawElnaz() 
	will automatically be called so anything you include in drawJim() will be drawn

	You can comment out both drawJim(); drawJeremy(); in utils_488.cpp::renderScene and
	nothing will be affected and we won't overwrite eachothers code
*/
void drawElnaz(const float jointParam[][4])
{
	glScalef(1, 1, 1);
	//drawarm();
	drawNewArm(jointParam);
	return;
}

void drawNewArm(const float jointParam[][4])
{
//glPushMatrix();
	float d1=1; // 1 meter
	float d2=1;
	float d3=1;
	float d4=1;

	GLfloat radius = 0.05; // in centimeters
	float lenght1=d1-radius ;
	float lenght2=d2-(2*radius) ;
	float lenght3=d3-radius ;

	drawAxis(1.0, ENABLE_AXIS);// draw at the origin

	frame2frame(jointParam[0],0,0);
	glPushMatrix();
	glTranslatef(0,0,lenght1/2.0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ELNAZ_COLOUR);
		glScalef(radius,radius,lenght1);
		glutSolidCube(1);
	glPopMatrix ();
	drawAxis(1.0, ENABLE_AXIS);

	frame2frame(jointParam[1],0,0);
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ELNAZ_COLOUR);
		glColor3f(1,0.5,0.5);
		glScalef(radius, radius, radius);
		glutSolidSphere (1,50,50); 
	glPopMatrix();

	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, ELNAZ_COLOUR);
		glTranslatef(0,0,radius+lenght2/2.0);
		glColor3f(0.5,1,0.5);
		glScalef(radius,radius,lenght2);
		glutSolidCube(1);
	glPopMatrix ();
	drawAxis(1.0, ENABLE_AXIS);

	frame2frame(jointParam[2],0,0);
	glPushMatrix();
		glColor3f(1,0.5,0.5);
		glScalef(radius, radius, radius);
		glutSolidSphere (1,50,50); 
	glPopMatrix();
	drawAxis(1.0, ENABLE_AXIS);

	frame2frame(jointParam[3],0,0);
	glPushMatrix();
		glTranslatef(0,0,-1*(lenght3/2.0));
		glColor3f(0.5,1,0.5);
		glScalef(radius,radius,lenght3);
		glutSolidCube(1);
	glPopMatrix ();
	drawAxis(1.0, ENABLE_AXIS);
//glPopMatrix ();
						 
}

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

