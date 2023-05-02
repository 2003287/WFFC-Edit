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
	int testingscroll;
	bool testcamera;
	bool canscroll;
	bool shiftDown;
	bool mouse_rb_down;
	bool mouse_lb_down;
};
