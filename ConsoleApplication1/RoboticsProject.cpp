// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include "utils_488.h"
#include "drawFunctions.h"

// TODO: Change the name to be more consistent.
const char* APPLICATION_NAME = "ENSC 488 Robot";

int main_window;

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutMainLoop();

	return 0;
}

