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

	//mouse position in space
	float mouse_x;
	float mouse_y;
	float mouse_old_x;
	float mouse_old_y;

	//camera mode and stuff
	int cameraMode;
	bool cameraswap;

	int testingscroll;
	bool mouse_moving;
	bool canscroll;
	bool shiftDown;

	//mouse buttons down
	bool mouse_rb_down;
	bool mouse_lb_down;

	//update the visuals of the object
	bool inspector;
	int game_mode;
	//for testing before an object
	bool testing_Anything;


	//copy paste and delete
	bool copyNum;
	bool copyFirst;
	bool paste;	
	bool delObject;

	bool Zoom;
};
