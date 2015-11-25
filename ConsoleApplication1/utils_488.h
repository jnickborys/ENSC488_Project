
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

void frame2frame(const GLfloat delta_frame[], GLint enable_vertice_axis, GLint no_line);
