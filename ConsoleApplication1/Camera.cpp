#include "stdafx.h"
#include "Camera.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include "stateInformation.h"
#include "global_constants.h"

Camera::Camera()
{
	// There has got to be a better way of initializing a pointer to an array
	_eye = new GLfloat[3];
	_eye[0] = -3;
	_eye[1] = 1;
	_eye[2] = -3;
	
	_focus = new GLfloat[3];
	_focus[0] = 0;
	_focus[1] = 0;
	_focus[2] = 0;
	
	_up = new GLfloat[3];
	_up[0] = 0;
	_up[1] = 1;
	_up[2] = 0;

	gluLookAt(_eye[0], _eye[1], _eye[2], _focus[0], _focus[1], _focus[2], _up[0], _up[1], _up[2]);
}

void Camera::Update()
{
	gluLookAt(_eye[0], _eye[1], _eye[2], _focus[0], _focus[1], _focus[2], _up[0], _up[1], _up[2]);
}

void Camera::FollowRobot(){
	glScalef(FT_TO_M, FT_TO_M, FT_TO_M);
	gluLookAt(robotPosition[0] + _eye[0], _eye[1], robotPosition[2] + _eye[2], robotPosition[0], _focus[1], robotPosition[2], _up[0], _up[1], _up[2]);
	glScalef(1/FT_TO_M, 1/FT_TO_M, 1/FT_TO_M);
}

void Camera::Move(const float _dir[])
{	
	_eye[0] += _dir[0];
	_eye[1] += _dir[1];
	_eye[2] += _dir[2];
}

void Camera::Rotate(const float _rot[])
{
	_focus[0] += _rot[0];
	_focus[1] += _rot[1];
	_focus[2] += _rot[2];

	return;
}

Camera::~Camera()
{
}
