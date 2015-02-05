/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/


// Common includes
#include "common.hpp"





int glInitGL()
{
	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		errorPrint("ERROR: glewInit failed\n");
		return 0;
	}
	return 1;
}