#include "stdafx.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include "utils_488.h"
#include "drawFunctions.h"
#include "global_constants.h"

#define PI 3.1415926535
//const GLfloat INCHES_TO_M = 0.0254;
#define INCHES_TO_M 0.0254;
#define M_TO_IN 1/0.0254;

void drawJeremy()
{

	//static const GLfloat R2 = 4.5 * INCHES_TO_M;
	static const GLfloat R2 = 4.5 * INCHES_TO_M;
	static const GLfloat R3 = 5 * INCHES_TO_M;

	const float W2a = 18;
	const float W2 = (2 * R3 + W2a) * INCHES_TO_M;

	const float W3 = 1.5 * INCHES_TO_M;
	const float D1 = 2 * 12.0 * INCHES_TO_M;
	
	const float W1 = 2 * R3 + W2 + 2 * W3;
	const float H2 = 1.5 * INCHES_TO_M;
	const float H1 = H2 + R2;

	const GLfloat jeremyLP[][4] = { 
									// Front Axle
									{ 0, W2 / 2, 0, 0},
									{ 0, 0, 0, D1/2 },
									{ 0, 0, 0, -D1/2},

									// Back Axle
									{ 0, -W2 / 2, 0, 0 },
									{ 0, 0, 0, D1 / 2 },
									{ 0, 0, 0, -D1 / 2 }

								};
	enum { FrontAxle, FLWheel, FRWheel, BackAxle, BLWheel, BRWheel };
	glPushMatrix(); // origin center of the robot
		// Move to the front Axle
		frame2frame(jeremyLP[FrontAxle], 1, 0);
		glPushMatrix();
			frame2frame(jeremyLP[FLWheel], 1, 0);
			drawWheel();
		glPopMatrix();
		glPushMatrix();
			frame2frame(jeremyLP[FRWheel], 1, 0);
			glRotatef(180, 0, 1, 0);
			drawWheel();
		glPopMatrix();
	glPopMatrix(); // Back to the Center

	glPushMatrix(); // origin center of the robot
		// Move to the front Axle
		frame2frame(jeremyLP[BackAxle], 1, 0);
		glPushMatrix();
			frame2frame(jeremyLP[BLWheel], 1, 0);
			drawWheel();
		glPopMatrix();
		glPushMatrix();
			frame2frame(jeremyLP[BRWheel], 1, 0);
			glRotatef(180, 0, 1, 0);
			drawWheel();
		glPopMatrix();
	glPopMatrix(); // Back to the Center

	// Draw the Body pushing for scaling
	glPushMatrix();
		glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN);
		glTranslatef(0, H1/2, 0);
		glScalef(W1, H1, D1);
		glutSolidCube(1);
	glPopMatrix();
	glTranslatef(0, H1 / 2, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, GREY);
}

void drawAxis(const GLfloat scale, const GLint enable)
{
	if (!enable)
	{
		return;
	}
	GLfloat color[4];
	glGetFloatv(GL_CURRENT_COLOR, color);
	glPushMatrix();

	glLineWidth(1);
	glPointSize(5);
	//glColor3f(1, 1, 1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, WHITE);
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glEnd();
	//glutSolidSphere(0.025, 12, 40);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, RED);
	//glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(scale, 0, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, GREEN);
	//glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, scale, 0);
	glEnd();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, BLUE);
	//glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, scale);
	glEnd();
	glLineWidth(1);
	glPointSize(1);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
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
	drawWheel();
	return;
}

void drawCircle(const GLfloat radius, const int num_segments)
{
	glBegin(GL_POLYGON);
	glNormal3d(0, 1, 0);

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
	static const GLfloat R1 = 3 * INCHES_TO_M;
	static const GLfloat R2 = 4.5 * INCHES_TO_M;
	static const GLfloat R3 = 5 * INCHES_TO_M;

	static const GLfloat H1 = R3 + 1 * INCHES_TO_M;

	static const GLfloat D2 = 3 * INCHES_TO_M;

	static const GLfloat lightBlack[] = { 0.35, 0.35, 0.35 };
	static const GLfloat darkerBlack[] = { 0.20, 0.20, 0.20 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, lightBlack);
	glPushMatrix();
	glScalef(R2, R2, D2);

	GLUquadric* wheel;
	wheel = gluNewQuadric();
	gluQuadricNormals(wheel, GLU_SMOOTH);
	glPushMatrix();
		gluCylinder(wheel, 1, 1, 1, 24, 24);
		glRotatef(270, 1, 0, 0);
		drawCircle(1, 24);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0, 0, 1);
		glRotatef(90, 1, 0, 0);
		drawCircle(1, 24);
	glPopMatrix();
	glPopMatrix();

	return;
}
