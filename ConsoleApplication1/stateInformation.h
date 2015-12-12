/* Contains all the DH parameters for our model stored globally */


/* 
	Forward Kinematic Parameters
*/
extern int alpha1;
extern int alpha2;
extern int alpha3;
extern int alpha4;
extern int theta1;
extern int d1;
extern int d2;
extern int d3;
extern int d4;

extern GLfloat forwardKinParam[][4];

/*
	Reverse Kinematic Paramters
*/
extern GLfloat inverseKinParam[3];


// Enables drawing of axis
extern GLint ENABLE_AXIS;
extern GLint ENABLE_INV_KIN;

// Force on the External Link
extern GLfloat staticForce[3];

// Static Torque Variables
extern GLfloat torque1;
extern GLfloat torque2;
extern GLfloat torque3;
