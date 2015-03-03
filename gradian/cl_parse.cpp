/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

Cvar *cl_scrollspeed;

#include "common.hpp"

bool gameInput[4];


void parseGameInput()
{
	if (gameInput[K_LEFT])
		viewXOffset--;
	if (gameInput[K_RIGHT])
		viewXOffset++;
	if (gameInput[K_UP])
		viewYOffset--;
	if (gameInput[K_DOWN])
		viewYOffset++;
}