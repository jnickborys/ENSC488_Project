#include "stdafx.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include <iostream>
#include "global_constants.h"
#include "UserInterface.h"
#include "stateInformation.h"

GLUI *menu;
GLUI_Spinner *tor1, *tor2, *tor3;

void panelHandler(GLint id)
{
	return;
}

void initStaticTorquePanel(GLUI *menu)
{
	GLUI_Panel *panel;
	panel = menu->add_panel("Static Torque Parameters");

	GLUI_Spinner *forcex, *forcey, *forcez;
	forcex = menu->add_spinner_to_panel(panel, "Force in X: ", GLUI_EDITTEXT_FLOAT, &staticForce[0], 9, panelHandler);
	forcey = menu->add_spinner_to_panel(panel, "Force in Y: ", GLUI_EDITTEXT_FLOAT, &staticForce[1], 10, panelHandler);
	forcez = menu->add_spinner_to_panel(panel, "Force in Z: ", GLUI_EDITTEXT_FLOAT, &staticForce[2], 11, panelHandler);
	tor1 = menu->add_spinner_to_panel(panel, "Torque on base", GLUI_EDITTEXT_FLOAT, &torque1, 12, panelHandler);
	tor2 = menu->add_spinner_to_panel(panel, "Torque on Link2", GLUI_EDITTEXT_FLOAT, &torque2, 13, panelHandler);
	tor3 = menu->add_spinner_to_panel(panel, "Torque on Link3", GLUI_EDITTEXT_FLOAT, &torque3, 14, panelHandler);
}

void initGUI (const int main_window, float DHParam[][4], float invKinParam[3]) {

	GLUI_Panel *panel1;
	GLUI_Panel *panel2;

	menu = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_LEFT);
	menu->set_main_gfx_window(main_window);
	menu->add_statictext("Forward Kinematic Parameters");

	panel1 = menu->add_panel("Angle [Range]");

	// Forward Kinematics Parameters
	GLUI_Spinner *box1, *box2, *box3, *box4, *box5, *box6;
	box1 = menu->add_spinner_to_panel(panel1, "Sphere [25, 155] ", GLUI_EDITTEXT_FLOAT, &DHParam[0][0], 0, panelHandler);
	box2 = menu->add_spinner_to_panel(panel1, "Arm 1 [0, 90] ", GLUI_EDITTEXT_FLOAT, &DHParam[1][2], 0, panelHandler);
	box3 = menu->add_spinner_to_panel(panel1, "Arm 2 [-150, -10] ", GLUI_EDITTEXT_FLOAT, &DHParam[2][2], 2, panelHandler);
	box4 = menu->add_spinner_to_panel(panel1, "Wrist [45, 315] ", GLUI_EDITTEXT_FLOAT, &DHParam[3][2], 3, panelHandler);
	box5 = menu->add_spinner_to_panel(panel1, "Pen Z [30, 175] ", GLUI_EDITTEXT_FLOAT, &DHParam[4][0], 4, panelHandler);
	box6 = menu->add_spinner_to_panel(panel1, "Pen X [30, 720] ", GLUI_EDITTEXT_FLOAT, &DHParam[5][2], 5, panelHandler);

	box1->set_alignment(GLUI_ALIGN_RIGHT);
	box1->set_float_limits(25, 155);
	box2->set_alignment(GLUI_ALIGN_RIGHT);
	box2->set_float_limits(0, 90);
	box3->set_alignment(GLUI_ALIGN_RIGHT);
	box3->set_float_limits(-150, -10);
	box4->set_alignment(GLUI_ALIGN_RIGHT);
	box4->set_float_limits(45, 315);
	box5->set_alignment(GLUI_ALIGN_RIGHT);
	box5->set_float_limits(30, 175);
	box6->set_alignment(GLUI_ALIGN_RIGHT);
	box6->set_float_limits(0, 720);

	menu->add_statictext("Inverse Kinematic Parameters");
	panel2 = menu->add_panel("Angle [Range]");

	// Inverse Kinematics
	GLUI_Spinner *xpos, *ypos, *zpos;
	xpos = menu->add_spinner_to_panel(panel2, "X Pos: ", GLUI_EDITTEXT_FLOAT, &invKinParam[0], 6, panelHandler);
	ypos = menu->add_spinner_to_panel(panel2, "Y Pos:", GLUI_EDITTEXT_FLOAT, &invKinParam[1], 7, panelHandler);
	zpos = menu->add_spinner_to_panel(panel2, "Z Pos: ", GLUI_EDITTEXT_FLOAT, &invKinParam[2], 8, panelHandler);

	initStaticTorquePanel(menu);

	menu->add_checkbox("Use Inverse Kinemematics", &ENABLE_INV_KIN);
	menu->add_checkbox("Show Axis", &ENABLE_AXIS);
}

void computeStaticBalanceTorque()
{
	GLfloat l1 = 1;
	GLfloat l2 = 1;
	GLfloat l3 = 1;

	GLfloat theta2 = 45.0;
	GLfloat theta3 = 45.0;

	GLfloat fx = staticForce[0];
	GLfloat fy = staticForce[1];
	GLfloat fz = staticForce[2];

	GLfloat s2 = sin(theta2 * DEGREES_TO_RAD);
	GLfloat c2 = cos(theta2 * DEGREES_TO_RAD);

	GLfloat s3 = sin(theta3 * DEGREES_TO_RAD);
	GLfloat c3 = cos(theta3 * DEGREES_TO_RAD);

	torque1 = fy*l3 + c3*fy*l2 + fx*l2*s3 + c2*fx*l1*s3 + c3*fx*l1*s2 - fy*l1*s2*s3 + c2*c3*fy*l1;
	torque2 = fy*l3 + c3*fy*l2 + fx*l2*s3;
	torque3 = fy*l3;

	//tor1->set_float_val(fy*l3 + c3*fy*l2 + fx*l2*s3 + c2*fx*l1*s3 + c3*fx*l1*s2 - fy*l1*s2*s3 + c2*c3*fy*l1);
	//tor2->set_float_val(fy*l3 + c3*fy*l2 + fx*l2*s3);
	//tor3->set_float_val(fy*l3);

	std::cout << "Before Sync Live\n";
	//menu->sync_live();
	std::cout << "After Sync Live\n";
}
