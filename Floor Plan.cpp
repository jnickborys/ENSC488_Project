// Floor Plan.cpp : Defines the entry point for the console application.
//


#include "stdafx.h" //PreCompiled Header Library
#include<stdio.h> // Standard Input and Output Library
#include<math.h> // Math Functions Library
#include<windows.h> // Windows API library
#include<GL/gl.h> // OpenGL Library
#include<GL/glut.h> // GLUT Library
#include "GL/glui.h" // Including the glui libraries (if needed)

#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4

// Keyboard and scene declarations
void myKeyboardFunc( unsigned char key, int x, int y );
void drawScene(void);
void initRendering();
void resizeWindow(int w, int h);
void drawcube(); //Declaring the name of the Function to Draw Cube
void moveRobot();

GLfloat rotate_angle=0; // Degrees the Sphere Rotates Evry Time it is Redrawn
GLfloat translation = -3.0; // Translation of the Sphere Evry Time it is Redrawn
int i,j; // Variable User as counter in the Loops
float red=1.0, blue=1.0, green=1.0; // variable for glur menu

// These variables control the current mode
int CurrentMode = 0;
const int NumModes = 7;


double robotPos [3]={0,0,0};

void moveRobot()
{
	float delta_t=0;
	float delta_x=0;
	float delta_y=0;
	float delta_z=0;
	static float delta_v [3] ={(0.1/1000.0)*1,0,0}; // m/s
	float x_new=0;
	float x_old=5.2;

	delta_t=glutGet(GLUT_ELAPSED_TIME); // milliseconds
	delta_x=(delta_v[0]*delta_t);
	delta_y=(delta_v[1]*delta_t);
	delta_z=(delta_v[2]*delta_t);

	x_new= (x_old+delta_x);

	glScalef(0.3,0.3,0.3);
	glTranslatef(5.2+(delta_x),0+(delta_y),-4.8+(delta_z));

	if (x_new=5.2) {
					delta_v [0] =0;
					delta_v [1] =0;
					delta_v [2] =(0.1/1000.0)*1;

					}
	//if (x_new>=0) {
					//delta_v [0] =(0.1/1000.0)*1;
					//delta_v [1] =0;
					//delta_v [2] =0;

					//}
	//if () {}
	//if () {}
	//if () {}
	//if () {}




}

void myKeyboardFunc( unsigned char key, int x, int y ) // Function to describe the harware use in OpenGL
{
switch ( key ) {
case ' ': // Space bar
// Increment the current mode, and tell operating system screen needs redrawing
CurrentMode = (CurrentMode+1)%NumModes;
glutPostRedisplay();
break;
case 27: // "27" is theEscape key
exit(1);
}
}

void init()
{
// Clear Color Buffer Before Drawing
glClearColor(0.0,0.0,0.0,0.0);


}
void display(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ClearColor Buffer
glColor3f (0.5,0.5,0.5);

// Using OpenGL Polygon function to draw a background with a desired color to indicate the Floor Plan

glBegin(GL_POLYGON);
glVertex3f(2.,0.0,0.0);
glVertex3f(2.0,0.0,-2.0);
glVertex3f(-2.0,0.0,-2.0);
glVertex3f(-2.0,0.0,0.0);

glEnd();

glPushMatrix ();
glColor3f(1,0.5,0.5);
glScalef(0.5,0.5,0.5);
glTranslatef(-2.8,0,-1.3);
glutSolidCube (1);
glPopMatrix ();

glPushMatrix ();
glColor3f(0.5,0.5,1);
glScalef(0.6,0.6,0.6);
glTranslatef(0.3,0,-2.4);
glutSolidCube (1);
glPopMatrix ();

glPushMatrix ();
glColor3f(0.5,1,1);
glScalef(0.3,0.3,0.3);
glTranslatef(5,0,-1.5);
glutSolidCube (1);
glPopMatrix ();

glPushMatrix ();

moveRobot();

glColor3f(1,0,0);
//glScalef(0.3,0.3,0.3);
//glTranslatef(5.2,0,-4.8);
glutSolidSphere(1,50,50);
glPopMatrix ();



glutSwapBuffers(); // Display Screen
}
void reshape(int w, int h)
{
if(h==0)
h = 1;
float ratio = 1.0*w/h;
glMatrixMode(GL_PROJECTION);
// gluPerspective(40.0,(GLdouble)w/(GLdouble)h,0.01,10.0);
gluPerspective(45,ratio,1,1000);
glMatrixMode(GL_MODELVIEW);
gluLookAt(2.0,4.0,1.5,0.0,0.0,0.0,0.0,1.0,0.0);
}

// Menu selection by clicking the right-button of the mouse

void processMenuEvents(int option) {
switch (option) {
case RED : red = 1.0; green = 0.0; blue = 0.0; break;
case GREEN : red = 0.0; green = 1.0; blue = 0.0; break;
case BLUE : red = 0.0; green = 0.0; blue = 1.0; break;
case WHITE : red = 1.0; green = 1.0; blue = 1.0; break;
}
}
// Chaning the color of the rectangular shaped-opject

void createGLUTMenus() {
int submenu;
submenu = glutCreateMenu(processMenuEvents);
glutAddMenuEntry("Red", RED);
glutAddMenuEntry("Blue", BLUE);
glutAddMenuEntry("Green", GREEN);
glutAddMenuEntry("White", WHITE);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void idle(void)
{

translation+=0.01; // The distance the sphere should be translated when redrawn
glutPostRedisplay(); // Redraw screen
}
int main2(int argc, char** argv)
{
//
// GLUT initialization Function For This Application
glutInit(&argc,argv);
// User Double Buffer and RGB Color Mode
glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGB);
// Initialize Window Width=800, Height=500
glutInitWindowSize(800,500);
// Create Application Window
//glutCreateWindow(argv[0]);
glutCreateWindow("Interactive OpenGL tutorial Sample: Ver. 2");
// Initilize OpenGL
init();
// Appoint display As Callback Display Function
glutDisplayFunc(display);
// Appoint reshape As Callback Reshape Function
glutReshapeFunc(reshape);
//
// Set up callback functions for key presses
glutKeyboardFunc( myKeyboardFunc ); // Handles "normal" ascii symbols
//-------------------
// Appoint idle As Callback Idle Function
glutIdleFunc(idle);
// call the function to create the menu
createGLUTMenus();
// Start Glut Event Handling Loop
glutMainLoop();
return 0;
}
