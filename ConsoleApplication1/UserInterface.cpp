#include "stdafx.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include "UserInterface.h"
#include "stateInformation.h"

void panelHandler(GLint id)
{
	return;
}

void initGUI (const int main_window, float DHParam[][4], float invKinParam[3]) {
	GLUI *menu;
	GLUI_Panel *panel1;
	GLUI_Panel *panel2;

	menu = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_LEFT);
	menu->set_main_gfx_window(main_window);
	menu->add_statictext("Forward Kinematic Parameters");

	panel1 = menu->add_panel("Angle [Range]");

	// Forward Kinematics Parameters
	GLUI_Spinner *box1, *box2, *box3, *box4, *box5, *box6;
	box1 = menu->add_spinner_to_panel(panel1, "Sphere [25, 155] ", GLUI_EDITTEXT_FLOAT, &DHParam[0][0], 0, panelHandler);
	box2 = menu->add_spinner_to_panel(panel1, "Arm 1 [0, 90] ", GLUI_EDITTEXT_FLOAT, &DHParam[1][0], 0, panelHandler);
	box3 = menu->add_spinner_to_panel(panel1, "Arm 2 [-150, -10] ", GLUI_EDITTEXT_FLOAT, &DHParam[2][0], 2, panelHandler);
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
	xpos = menu->add_spinner_to_panel(panel2, "Sphere [25, 155] ", GLUI_EDITTEXT_FLOAT, &invKinParam[0], 0, panelHandler);
	ypos = menu->add_spinner_to_panel(panel2, "Arm 1 [0, 90] ", GLUI_EDITTEXT_FLOAT, &invKinParam[1], 0, panelHandler);
	zpos = menu->add_spinner_to_panel(panel2, "Arm 2 [-150, -10] ", GLUI_EDITTEXT_FLOAT, &invKinParam[2], 2, panelHandler);

	//menu2->add_checkbox("Show Skeleton", &show_skeleton);
	menu->add_checkbox("Show Axis", &ENABLE_AXIS);
}