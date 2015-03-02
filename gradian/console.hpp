/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

extern void Con_Execute(string cmd);

extern void Con_Print(string msg);


extern void initConsole();

extern void drawConsole();


extern Cvar *con_lines;

extern string con_input_line;

enum constatus
{
	CONSOLE_OFF,
	CONSOLE_FULL,
	CONSOLE_PARTIAL
};

extern constatus console_status;