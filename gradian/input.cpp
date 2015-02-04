/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"

// TODO(Jukki) make this whole thing handled better
void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	static bool bDepthClampingActive = false;
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		debugPrint("we pressed E\n");
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int initInput()
{
	glfwSetKeyCallback(gradian.main_window, inputCallback);

	debugPrint("initInput done\n");
	return 1;
}