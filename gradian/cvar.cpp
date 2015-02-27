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

map<string, Cvar *> cvarList;

using namespace std;
using namespace boost;

void loadConfig()
{
	string path = "configs/config.cfg";
	path = MAINDIR + path;
	std::ifstream infile(path);

	for (string line; getline(infile, line);)
	{
		trim(line);

		if (line[0] == '#') //ignore comments
			continue;

		vector<string> cvar;

		boost::split(cvar, line, boost::is_any_of(":"));

		if (cvar.size() == 2)
		{
			string cvarName = cvar[0];
			string cvarValue = cvar[1];
			trim(cvarName);
			trim(cvarValue);
			Cvar *variable = cvarList[cvarName];
			if (variable)
			{
				*variable = cvarValue;
			}
			else
			{
				debugPrint("Unknown cvar in config file " + cvarName);
			}
		}
	}
}


void setupCvars()
{
	vid_width = new Cvar("vid_width", "Stores windows width", 800, SAVE);
	vid_height = new Cvar("vid_height", "Stores windows height", 600, SAVE);
	vid_fullscreen = new Cvar("vid_fullscreen", "Is the game run on windowed (0), full screen (1) or windowed fullscreen (2)", 0, SAVE);
	vid_monitor = new Cvar("vid_monitor", "Chose which monitor to use for fullscreen (0 is primary display)", 0, SAVE);
	vid_vsync = new Cvar("vid_vsync", "Turn on vsync or turn it of", 0, SAVE);
}


void saveCvars()
{

}

int initCvars()
{
	setupCvars();
	loadConfig();

	return 1;
}