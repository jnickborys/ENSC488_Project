#include "stdafx.h"
#include "Camera.h"

#include <gl\glui.h>
#include <gl\glut.h>
#include <gl\GLU.h>
#include <gl\GL.h>


Camera::Camera()
{
	// There has got to be a better way of initializing a pointer to an array
	_eye = new GLfloat[3];
	_eye[0] = 10;
	_eye[1] = 10;
	_eye[2] = 10;
	
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
