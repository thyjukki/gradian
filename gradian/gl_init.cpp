/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/


// Common includes
#include "common.hpp"





void glfw_error_callback(int error, const char* description)
{
	errorPrint("GLFW error " + to_string(error) + ": " + description + "\n");
}


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

	glfwSetErrorCallback(glfw_error_callback);
}