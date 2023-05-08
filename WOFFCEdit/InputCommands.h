#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool rotRight;
	bool rotLeft;
	bool fDown;
	float mouse_x;
	float mouse_y;
	float mouse_old_x;
	float mouse_old_y;
	int cameraMode;
	bool cameraswap;

	int testingscroll;
	bool mouse_moving;
	bool canscroll;
	bool shiftDown;
	bool mouse_rb_down;
	bool mouse_lb_down;

	bool inspector;
	int game_mode;
	//for testing before an object
	bool testing_Anything;
};
