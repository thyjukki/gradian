/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"

map<string, Cvar *> cvarList;

void Cvar::setupCvar()
{
	if (cvarList.count(this->name))
	{
		throw MyException("Tried to define allready defined cvar " + this->name);
		return;
	}
	
	this->baseValue = this->value;

	cvarList[this->name] = this;
}

int initCvars()
{
#include "cvarlist.hpp"

	return 1;
}