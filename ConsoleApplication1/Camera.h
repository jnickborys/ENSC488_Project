#pragma once

class Camera
{
public:
	Camera();
	~Camera();

	void Update();

	/* Take in a Velocity and calculate the new position based on the velocity*/
	void Move(const float _dir[]);

	/* Changes the focus of the camera */
	void Rotate(const float _rot[]);

	void FollowRobot();

private:
	float *_eye, *_focus, *_up;
};

