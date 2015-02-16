/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"

Cvar *vid_width;
Cvar *vid_height;
Cvar *vid_fullscreen;
Cvar *vid_monitor;

/*
	void reshape (w, h)

	Reshapes the screen in case the dimension changes, also sets the perspective matrix to correct one, to suit new size
*/
void reshape(GLFWwindow* window, int w, int h)
{
	*vid_height = h;
	*vid_width = w;
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);
}
int initDisplay()
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
	if (vid_fullscreen->toInt() == 1)
	{
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		int monitorIndex = vid_monitor->toInt();
		if (count < monitorIndex + 1)
		{
			monitorIndex = 0;
		}
		const GLFWvidmode* mode = glfwGetVideoMode(monitors[monitorIndex]);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		gradian.main_window = glfwCreateWindow(vid_width->toInt(), vid_height->toInt(), "Gradian WIP", monitors[monitorIndex], nullptr);
	}
	else
		gradian.main_window = glfwCreateWindow(vid_width->toInt(), vid_height->toInt(), "Gradian WIP", nullptr, nullptr);


	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	glfwSetWindowSizeCallback(gradian.main_window, reshape);
	if (!gradian.main_window)
	{
		errorPrint("ERROR: glfwCreateWindow failed\n");
		return 0;
	}
	glfwMakeContextCurrent(gradian.main_window);


	// Init viewport
	reshape(gradian.main_window, vid_width->toInt(), vid_height->toInt());

	return 1;
}