/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"

#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;
glm::vec2 cursorLocation;

enum actionType
{
	KEY_COMMAND,
	KEY_TOGGLE,
	KEY_INCREASE,
	KEY_DECREASE
};
class KeyAction
{
public:
	actionType type;
	string command;
	KeyAction(actionType tp)
	{
		this->type = tp;
	}

	virtual void buttonDown()=0;

	virtual void buttonUp()=0;
};

class KeyActionConsole: public KeyAction
{
public:
	KeyActionConsole(actionType tp, string cmd) : KeyAction(tp)
	{
		this->command = cmd;
	}

	void buttonDown()
	{
		switch (this->type)
		{
		case KEY_COMMAND:
			Con_Execute(this->command);
			break;
		case KEY_TOGGLE:
		case KEY_INCREASE:
		case KEY_DECREASE:
			//
			break;
		}
	}

	void buttonUp()
	{
		switch (this->type)
		{
		case KEY_COMMAND:
		case KEY_TOGGLE:
		case KEY_INCREASE:
		case KEY_DECREASE:
			break;
		}
	}
};

struct keystate
{
	bool down;
	double downSince;
	double timeHeld;
	KeyAction *action;
};

map<int, keystate> keyList;

// TODO(Jukki) make this whole thing handled better
void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (console_status != CONSOLE_OFF)
	{
		if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
			console_status = CONSOLE_OFF;
		if (action == GLFW_PRESS && key == GLFW_KEY_ENTER)
		{
			Con_Execute(con_input_line);
			con_input_line = "";
		}
		if (action == GLFW_PRESS && key == GLFW_KEY_BACKSPACE)
			con_input_line.pop_back();
		return;
	}

	if (keyList.count(key) > 0)
	{

		switch (action)
		{
			case GLFW_PRESS:
				if (!keyList[key].down)
				{
					keyList[key].down = true;
					keyList[key].downSince = glfwGetTime();
					keyList[key].action->buttonDown();
				}
				break;
			case GLFW_RELEASE:
				keyList[key].down = false;
				keyList[key].timeHeld = glfwGetTime() - keyList[key].downSince;
				keyList[key].downSince = 0.0f;
				keyList[key].action->buttonUp();
				break;
		}
	}
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	if (console_status == CONSOLE_OFF)
		return;

	con_input_line += codepoint;
}

void mousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	cursorLocation.x = (float)xpos;
	cursorLocation.y = (float)ypos;
}

void loadInputConfig()
{
	string path = "configs/keys.cfg";
	path = MAINDIR + path;
	std::ifstream infile(path);

	for (string line; getline(infile, line);)
	{
		trim(line);

		if (line[0] == '#') //ignore comments
			continue;

		vector<string> keybind;

		boost::split(keybind, line, boost::is_any_of(":"));

		if (keybind.size() == 2)
		{
			string bind = keybind[0];
			string key = keybind[1];
			trim(bind);
			trim(key);
			if (bind[0] == '-') //thease are used for actual button presses TODO(Jukki)
			{

			}
			else //other wise assume its a console command
			{

				int keyNum;
				try {
					keyNum = boost::lexical_cast<int>(key);

					KeyAction *action;

					if (bind[0] == '|') //toggle cvar
					{
						bind.erase(0, 1);
						action = new KeyActionConsole(KEY_TOGGLE, bind);
					}
					else if (bind[0] == '/') //increase cvar
					{
						bind.erase(0, 1);
						action = new KeyActionConsole(KEY_TOGGLE, bind);
					}
					else if (bind[0] == '\\') //decrease cvar
					{
						bind.erase(0, 1);
						action = new KeyActionConsole(KEY_TOGGLE, bind);
					}
					else
						action = new KeyActionConsole(KEY_COMMAND, bind);

					keyList[keyNum] = { false, 0.0f, 0.0f, action };
				}
				catch (boost::bad_lexical_cast const&) {
					Con_Print("Error: keys.cfg input string was not valid");
				}
			}
		}
	}
}

int initInput()
{
	loadInputConfig();
	cursorLocation = glm::vec2(0, 0);
	glfwSetKeyCallback(gradian.main_window, inputCallback);

	glfwSetCharCallback(gradian.main_window, character_callback);

	glfwSetCursorPosCallback(gradian.main_window, mousePosCallback);

	glfwSetInputMode(gradian.main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 1;
}