/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

// Cvars work similiar how valve source engine and id1 quake engines work.
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
extern void debugPrint(string message);
extern void errorPrint(string message);

enum cvarFlag{
	NONE = (1 << 0),
	SAVE = (1 << 2),
};


class Cvar;
extern std::map<std::string, Cvar *> cvarList;
class Cvar
{
public:
	string name = "";
	string description = "";
	string value = "";
	string baseValue = "";
	cvarFlag flags = NONE;
	Cvar(string a, string b) : name(a), description(b)
	{
		this->baseValue = this->value;

		cvarList[this->name] = this;
	}
	Cvar(string a, string b, int value) : name(a), description(b)
	{
		this->value = to_string(value);

		this->baseValue = this->value;

		cvarList[this->name] = this;
	}
	Cvar(string a, string b, float value) : name(a), description(b)
	{
		this->value = to_string(value);

		this->baseValue = this->value;

		cvarList[this->name] = this;
	}
	Cvar(string a, string b, string c) : name(a), description(b), value(c)
	{

		this->baseValue = this->value;

		cvarList[this->name] = this;
	}

	Cvar(string a, string b, cvarFlag d) : name(a), description(b), flags(d)
	{

		this->baseValue = this->value;

		cvarList[this->name] = this;
	}
	Cvar(string a, string b, int value, cvarFlag d) : name(a), description(b), flags(d)
	{
		this->value = to_string(value);

		this->baseValue = this->value;

		cvarList[this->name] = this;
	}
	Cvar(string a, string b, float value, cvarFlag d) : name(a), description(b), flags(d)
	{
		this->value = to_string(value);

		this->baseValue = this->value;

		cvarList[this->name] = this;
	}
	Cvar(string a, string b, string c, cvarFlag d) : name(a), description(b), value(c), flags(d)
	{
		this->baseValue = this->value;

		cvarList[this->name] = this;
	}

	Cvar& operator=(string value)
	{
		this->value = value;

		return *this;
	}

	Cvar& operator=(float value)
	{
		this->value = to_string(value);

		return *this;
	}

	Cvar& operator=(int value)
	{
		this->value = to_string(value);

		return *this;
	}

	int toInt()
	{
		return atoi(this->value.c_str());
	}

	float toFloat()
	{
		return (float)atof(this->value.c_str());
	}

	string toString()
	{
		return this->value;
	}
};


extern int initCvars();
extern void saveCvars();