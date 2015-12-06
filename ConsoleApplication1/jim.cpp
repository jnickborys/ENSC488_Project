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

	glScalef(2.0f, 2.0f, 2.0f);

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
	glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glutSolidSphere(0.5, 20, 20);
	glPopMatrix();


	//Wrist Carpals : rotation 
	frame2frame(WristLinkParam[carpols], 0, 0);
	drawAxis(1.0);
	//Wrist Extender
	glPushMatrix();
		glScalef(1.5, 0.5, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		//Wrist End Effector: 
		frame2frame(WristLinkParam[clamp_origin], 0, 0);
		drawAxis(1.0);
	
		glPushMatrix();
			glScalef(0.5, 0.5, 4.0);
			glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();       //Remember clamp_origin
			frame2frame(WristLinkParam[left_clamp], 0, 0);
			drawAxis(1.0);
	
			glScalef(0.50f, 0.50f, 0.5f);
			glTranslatef(1.50f, -0.50f, 0.0f);
			glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
			drawClamp();

		glPopMatrix();


		glPushMatrix();      //Remeber clamp_origin
			frame2frame(WristLinkParam[right_clamp], 0, 0);
			drawAxis(1.0);

			glScalef(0.50f, 0.5f, 0.5f);
			glTranslatef(0.5f, -0.50f, 0.0f);
			drawClamp();

		glPopMatrix();
	
	glPopMatrix();
	
}

void drawClamp() {
	
	float dipVal = 0.4f;
	glColor3f(0, 255, 0);   //Choose Color

	glBegin(GL_QUADS); //Begin quadrilateral coordinates
	//Wedge Front
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, dipVal, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);

	//Wedge lower left
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, dipVal, 1.0f);
	glVertex3f(0.0f, dipVal, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	//Wedge Back
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, dipVal, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	//Wedge Right
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	//Wedge Top
	glVertex3f(1.0f, dipVal, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, dipVal, 1.0f);

	//Wedge Bottom
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glEnd(); //End quadrilateral coordinates

}