/* Contains all the DH parameters for our model stored globally */


/* 
	Forward Kinematic Parameters
*/
extern int alpha1;
extern int alpha2;
extern int alpha3;
extern int alpha4;
extern int theta1;
//extern float d1;
//extern float d2;
//extern float d3;
//extern float d4;

extern GLfloat forwardKinParam[][4];

/*
	Reverse Kinematic Paramters
*/
extern GLfloat inverseKinParam[3];


// Enables drawing of axis
extern GLint ENABLE_AXIS;
extern GLint ENABLE_INV_KIN;
extern GLint ENABLE_MOVEMENT;
extern GLint ENABLE_CAMERA_FOLLOW;

// Force on the External Link
extern GLfloat staticForce[3];

// Static Torque Variables
extern GLfloat torque1;
extern GLfloat torque2;
extern GLfloat torque3;

extern GLfloat robotPosition[];
extern GLfloat robotFacing;
extern GLfloat velocity;

extern GLfloat angularVelocity;
extern GLfloat angularAccel;

extern GLint prev_time;

extern GLint state;

// variable for trajectory gen
extern GLfloat a_[];
extern GLint t0, tf, thalf;
extern GLfloat TrajectoryTheta[];
