/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/


// Common includes
#include "common.hpp"


// TODO(Jukki) Move to better place
int window_width = 800;
int window_height = 600;


int glInitWindow()
{

	// Init glfw first and set up window
	if (glfwInit() != GL_TRUE)
	{
		errorPrint("ERROR: glfwInit failed\n");
		return 0;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// TODO(Jukki) Save window data to better place maybe?
	// Maeybe put this to better place, remember to load the data from a file
	gradian.main_window = glfwCreateWindow(window_width, window_height, "Gradian WIP", nullptr, nullptr);


	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	glfwSetWindowSizeCallback(gradian.main_window, reshape);
	if (!gradian.main_window)
	{
		errorPrint("ERROR: glfwCreateWindow failed\n");
		return 0;
	}
	glfwMakeContextCurrent(gradian.main_window);


	// Init GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		errorPrint("ERROR: glewInit failed\n");
		return 0;
	}

	// Init viewport
	reshape(gradian.main_window, window_width, window_height);

	debugPrint("glInitWindow done\n");
	return 1;
}