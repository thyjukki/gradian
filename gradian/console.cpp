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
#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o

using namespace std;
using namespace boost;

Cvar *con_lines;

class ConEntry
{
public:
	posix_time::ptime time;
	string line;
	ConEntry(string line, posix_time::ptime time)
	{
		this->line = line;
		this->time = time;
	}
};

vector<ConEntry *> consoleBuffer;

Cvar *developer;


typedef void(*pfunc)(string);

map<string, pfunc> commandList;
string con_input_line;



void exitCMD(string parm)
{
	// TODO(Jukki) Replace this with function that points to true "close the app" function
	glfwSetWindowShouldClose(gradian.main_window, GL_TRUE);
}


void toggleconsoleCMD(string parm)
{
	if (gradian.consoleActive)
		gradian.consoleActive = false;
	else
		gradian.consoleActive = true;
}

void mapCMD(string parm)
{

	// TODO(Jukki) Unload previous map

	//currentMap = parm;
	unloadMap();
	setupMap(parm);
}



void Con_Print(string msg)
{
	consoleBuffer.push_back(new ConEntry(msg, posix_time::microsec_clock::local_time()));
	debugPrint(msg);
}
void Con_DPrint(string msg)
{
	if (developer->isTrue())
		Con_Print(msg);
}

void Con_Execute(string cmd)
{

	vector<string> cmdSplit;

	split(cmdSplit, cmd, is_any_of(" "));
	string command = cmd;
	string parameter = "";

	if (cmdSplit.size() >= 2) // TODO(Jukki) Do we need more than one paramter?
	{
		command = cmdSplit[0];
		parameter = cmdSplit[1];
		trim(command);
		trim(parameter);
	}

	if (commandList.count(command) > 0)
	{
		pfunc f = commandList[command];
		(*f)(parameter);
	}
	else if (cvarList.count(command) > 0)
	{
		cvarList[command]->operator=(parameter);

		Con_Print(cvarList[command]->name + " value set to " + parameter);
	}
	else
	{
		Con_Print("Unknwon command " + command);
	}
}


void registerCMD(string name, pfunc command)
{
	if (commandList.count(name) > 0)
	{
		Con_Print("Command " + name + " already registered");
		return;
	}
	commandList[name] = command;
}

void drawConsolePartialy()
{
	Draw_Rectangle(0, 0, vid_width->toInt(), (con_lines->toInt() + 2)*10, glm::vec4(0, 0, 0, 1), 0.0f);

	int conLen = consoleBuffer.size();

	if (conLen < 1)
		return;

	int lines = min(conLen, con_lines->toInt());
	int y = 0;
	for (int i = lines; i >= 1; i--)
	{
		int index = conLen - i;

		render_text(0, 0 + y, 10, 10, glm::vec4(1, 1, 1, 1), consoleBuffer[index]->line);
		y += 10;

	}
	
	render_text(0, (con_lines->toInt() + 1) * 10, 10, 10, glm::vec4(1, 1, 1, 1), con_input_line);
}

void drawConsoleMsg()
{
	if (!developer->isTrue())
		return;
	int conLen = consoleBuffer.size();

	if (conLen < 1)
		return;
	posix_time::ptime curTime = posix_time::microsec_clock::local_time();

	int lines = min(conLen, 3);
	int y = 0;
	for (int i = lines; i >= 1; i--)
	{
		int index = conLen - i;
		posix_time::time_duration timeAllive = curTime - consoleBuffer[index]->time;

		if (timeAllive.total_seconds() < 5)
		{
			render_text(0, 0 + y, 10, 10, glm::vec4(1, 1, 1, 1), consoleBuffer[index]->line);
			y += 10;
		}

	}
}

void drawConsole()
{
	switch (gradian.consoleActive)
	{
	case true:
		drawConsolePartialy();
		break;
	case false:
		drawConsoleMsg();
		break;
	}
}



void initConsole()
{
	registerCMD("exit", exitCMD);
	registerCMD("map", mapCMD);
	registerCMD("toggleconsole", toggleconsoleCMD);
}