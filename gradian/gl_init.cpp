/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/


// Common includes
#include "common.hpp"





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
	gradian.main_window = glfwCreateWindow(vid_width.toInt(), vid_height.toInt(), "Gradian WIP", nullptr, nullptr);


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
	reshape(gradian.main_window, vid_width.toInt(), vid_height.toInt());

	debugPrint("glInitWindow done\n");
	return 1;
}