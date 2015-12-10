// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include "stateInformation.h"
#include "utils_488.h"
#include "drawFunctions.h"
#include "UserInterface.h"

// TODO: Change the name to be more consistent.
const char* APPLICATION_NAME = "ENSC 488 Robot";

int main_window;

int alpha1 = 0;
int alpha2 = 0;
int alpha3 = 0;
int alpha4 = 0;
int theta1 = 0;
int d1 = 1;
int d2 = 1;
int d3 = 1;
int d4 = 1;

GLfloat forwardKinParam[][4] = { { theta1, 0, alpha1, 0 },
							{ 0, 0, alpha2, d1 },
							{ 0, 0, alpha3, d2 },
							{ 0, 0, alpha4, d3 },
							{ 0, 0, 0, 0 },
							{ 0, 0, 0, 0 },
							{ 0, 0, 0, 0 },
							};

GLfloat inverseKinParam[3] = { 0, 0, 0 };
GLint ENABLE_AXIS = 0;

// GLUT Specifics
void idle(void)
{
	glutSetWindow(main_window);
	glutPostRedisplay();
	return;
}

int _tmain(int argc, char argv[])
{
	glutInit(&argc, &argv);

	// GLUT_DOUBLE Enables double buffered mode, essentially prevents
	// screen flickering by first drawing to a memory buffer, then
	// the memory buffer is copied to the drawing surface on the screen

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(200, 200);
	main_window = glutCreateWindow(APPLICATION_NAME);

	// According to GLUI Doc idle function should be registered with GLUI
	GLUI_Master.set_glutKeyboardFunc(keyBoardEventHandler);
	GLUI_Master.set_glutSpecialFunc(specialCharEventHandler);
	GLUI_Master.set_glutMouseFunc(mouseEventHandler);
	GLUI_Master.set_glutDisplayFunc(renderScene);
	GLUI_Master.set_glutReshapeFunc(reshapeEventHandler);
	GLUI_Master.set_glutIdleFunc(idle);
	GLUI_Master.auto_set_viewport();

	initGUI(main_window, forwardKinParam, inverseKinParam);

	// Enables Basic Lighting and Shading
	// https://www.cse.msu.edu/~cse872/tutorial3.html
	// Makes glColor* not useful can change colours by 
	// changing material properties

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glutMainLoop();

	return 0;
}

