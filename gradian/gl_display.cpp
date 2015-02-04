/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"

Cvar vid_width = Cvar("vid_width", "Stores windows width", 800, SAVE);
Cvar vid_height = Cvar("vid_height", "Stores windows height", 600, SAVE);
/*
	void reshape (w, h)

	Reshapes the screen in case the dimension changes, also sets the perspective matrix to correct one, to suit new size
*/
void reshape(GLFWwindow* window, int w, int h)
{
	vid_height = h;
	vid_width = w;
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
}

int initDisplay()
{
	return 1;
}