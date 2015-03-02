/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

//this is temp, needs to be edited when not working.
#define MAINDIR std::string("../gradian/")

enum gameState
{
	MENU,
	LOADING,
	GAME
};
class Gradian
{
public:
	GLFWwindow	*main_window;
	gameState	state;
	GameBoard	*board;
	string		map;
	bool		consoleActive;
};

extern Gradian gradian;

extern Cvar *developer;