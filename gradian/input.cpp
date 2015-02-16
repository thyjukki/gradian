/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"

glm::vec2 cursorLocation;

// TODO(Jukki) make this whole thing handled better
void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		debugPrint("we pressed E\n");
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


void mousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	cursorLocation.x = (float)xpos;
	cursorLocation.y = (float)ypos;
}

int initInput()
{
	cursorLocation = glm::vec2(0, 0);
	glfwSetKeyCallback(gradian.main_window, inputCallback);

	glfwSetCursorPosCallback(gradian.main_window, mousePosCallback);

	glfwSetInputMode(gradian.main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	debugPrint("initInput done\n");
	return 1;
}