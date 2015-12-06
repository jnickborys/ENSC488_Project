// Jim's Implemented Source Code
#include "stdafx.h"
#include "jim.h"

#include<math.h> // Math Functions Library
#include<windows.h> // Windows API library
#include<GL/gl.h> // OpenGL Library
#include<GL/glut.h> // GLUT Library
#include "GL/glui.h" // Including the glui libraries (if needed)
#include "utils_488.h"
#include "drawFunctions.h"


/* 
	Jim Include all your draw code in drawJim(), drawJim() will automatically be called so
	anything you include in drawJim() will be drawn to the canvas

	You can comment out both drawElnaz(); drawJeremy(); in utils_488.cpp::renderScene and 
	nothing will be affected and we won't overwrite eachothers code
*/


void drawJim(const float WristLinkParam[][4])
{

	glScalef(1, 1, 1);
	drawWrist(WristLinkParam);

	return;
}

void drawWrist(const float WristLinkParam[][4]) {
	//float RotationDeg = 24;  // should make a dynamic value that change rotation.
	//float DistFromOrigin = 2;
	//GLfloat WristRotate[] = {RotationDeg,1,0,0 };
	//GLfloat WristExtent[] = {RotationDeg,1,0,0 };
	//GLfloat MoveClamp[] = {RotationDeg,1,0,0 };
	enum
	{
		//0 ,1,2,3 
		carpols,clamp_origin,left_clamp, right_clamp,
	};


	//Wrist Base:  Joint to the arm. 
	drawAxis(1.0);
	
	
	//Wrist Carpals : rotation 
	frame2frame(WristLinkParam[carpols], 0, 0);
	drawAxis(1.0);

	glPushMatrix();
	//Wrist End Effector: 
	frame2frame(WristLinkParam[clamp_origin], 0, 0);
	drawAxis(1.0);


	glPushMatrix();       //Remember clamp_origin
	frame2frame(WristLinkParam[left_clamp], 0, 0);
	drawAxis(1.0);
    glPopMatrix();


	glPushMatrix();      //Remeber clamp_origin
	frame2frame(WristLinkParam[right_clamp], 0, 0);
	drawAxis(1.0);
	glPopMatrix();

	glPopMatrix();
	////Wrist Hand
	//glPushMatrix();
	//glScalef(1, 1, 1);
	//glTranslatef(0, 1, 0);
	//glColor3f(1.0, 1.0, 0.0);
	//glutSolidCube(1);
	//glPopMatrix();
	// 

	////glPushMatrix();
	////glTranslatef(0, -7, 0);
	////glColor3f(0.5, 1, 0.5);
	////glScalef(1.6, 12, 1.6);
	////glutSolidCube(1);
	////glPopMatrix();

	////glPushMatrix();
	////glColor3f(1, 0.5, 0.5);
	////glTranslatef(0, -14, 0);
	////glutSolidSphere(1, 50, 50);
	////glPopMatrix();

	////glPushMatrix();
	////glTranslatef(0, -21, 0);
	////glColor3f(0.5, 1, 0.5);
	////glScalef(1.6, 12, 1.6);
	////glutSolidCube(1);
	////glPopMatrix();

	////glPushMatrix();
	////glTranslatef(0, 7, 0);
	////glColor3f(0.5, 1, 0.5);
	////glScalef(1.6, 12, 1.6);
	//glutSolidCube(1);
	//glPopMatrix();


	
}

