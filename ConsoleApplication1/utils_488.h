
// GLUT and GLUI Callback threads
void keyBoardEventHandler(unsigned char key, int x, int y);

//void draw(void);
void idle();
void initRendering();

void renderScene();
void reshapeEventHandler(int w, int h);
void specialCharEventHandler(int key, int x, int y);
void mouseEventHandler(int button, int state, int x, int y);

void getSeparationVector(const GLfloat v1[], const GLfloat v2[], GLfloat r[]);
void drawCamera(const GLfloat eye[], const GLfloat focus[], const GLfloat rotc[], const GLint draw_rot);

/*
Draws a position using a delta_frame which is a difference between two reference frames A and B.

delta_frame is of size 4and has the parameters:
alpha:	angle (in deg) to rotate around z axis to bring the frame to x'
a:		offset (in meters) from x' axis to the new Position in frame 2
theta:  angle (in deg) to align z' axis to the new z'' axis in frame 2
d:		offset (in deg) move the newly aligned position
*/
void frame2frame(const GLfloat delta_frame[], GLint enable_vertice_axis, GLint no_line);
