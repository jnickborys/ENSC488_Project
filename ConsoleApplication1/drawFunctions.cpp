#include "stdafx.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#define PI 3.1415926535

void drawAxis(const GLfloat scale)
{
	glPushMatrix();

	glLineWidth(1);
	glPointSize(5);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();
	//glutSolidSphere(0.025, 12, 40);

	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(scale, 0, 0);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, scale, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, scale);
	glEnd();
	glLineWidth(1);
	glPointSize(1);
	glPopMatrix();
}


void drawFloor(const GLfloat width, const GLfloat height, const GLfloat depth)
{
	const static GLfloat thickness = 1.0 / 100.0; // 1 cm to meters 

	// Set the colour to grey
	glColor3f(0.2, 0.2, 0.2);

	//glPushMatrix();
	//glTranslatef(0, depth, 0);
	//glScalef(width, thickness, height);
	//glutSolidCube(1);
	//glPopMatrix();
	GLfloat p1[] = { -width / 2, depth, -height / 2 };
	GLfloat p2[] = { -width / 2, depth, height / 2 };
	GLfloat p3[] = { width / 2, depth, height / 2 };
	GLfloat p4[] = { width / 2, depth, -height / 2 };

	glBegin(GL_POLYGON);
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p4);
	glEnd();
}

void drawPyramid(GLint show_skeleton)
{
	if (show_skeleton)
		return;
	const GLfloat height = sqrt(2);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1, 0, -1);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1, 0, 1);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1, 0, -1);

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1, 0, -1);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1, 0, 1);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1, 0, 1);

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0, height, 0);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1, 0, -1);

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1, 0, -1);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, height, 0);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1, 0, -1);

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1, 0, -1);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, height, 0);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1, 0, 1);

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1, 0, 1);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, height, 0);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1, 0, 1);

	glEnd();
}

void drawRectBox(const GLfloat width, const GLfloat height, GLfloat depth)
{

	// draw top and bottom
	drawFloor(width, height, 0);
	drawFloor(width, height, depth);

	glPushMatrix();
	glTranslatef(0, 0, depth / 2.0);

	glPushMatrix(); //save center 
	glTranslatef(-width / 2, 0, 0);
	glRotatef(90, 1, 0, 0);
	glPopMatrix(); // out of center

	glPopMatrix(); // back to original frame

}

void drawBase()
{
	return;
}

void drawCircle(const GLfloat radius, const int num_segments)
{
	glBegin(GL_POLYGON);

	for (int i = 0; i < num_segments; ++i)
	{
		GLfloat theta = 2.0 * PI * GLfloat(i) / GLfloat(num_segments);
		GLfloat dx = radius * cos(theta);
		GLfloat dz = radius * sin(theta);
		glVertex3f(dx, 0, dz);
	}
	glEnd();
}

void drawWheel()
{
	GLUquadric* wheel;
	wheel = gluNewQuadric();
	gluQuadricNormals(wheel, GLU_SMOOTH);
	gluCylinder(wheel, 4.5, 4.5, 3, 12, 12);
	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		drawCircle(4.5, 12);
	glPopMatrix();
	return;
}
