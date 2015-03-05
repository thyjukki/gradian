/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/


#include "common.hpp"

Cvar *cl_scrollspeed;

bool gameInput[4];


void parseGameInput()
{
	if (gameInput[K_LEFT])
		viewXOffset -= cl_scrollspeed->toInt()*gradian.deltaTime;
	if (gameInput[K_RIGHT])
		viewXOffset += cl_scrollspeed->toInt()*gradian.deltaTime;
	if (gameInput[K_UP])
		viewYOffset -= cl_scrollspeed->toInt()*gradian.deltaTime;
	if (gameInput[K_DOWN])
		viewYOffset += cl_scrollspeed->toInt()*gradian.deltaTime;
}