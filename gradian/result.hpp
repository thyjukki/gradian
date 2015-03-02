/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#pragma once
#include <string>

class Result
{
public:
	bool succes;

	std::string message;

	Result(std::string message, bool succes)
	{
		this->message = message;
		this->succes = succes;
	}


private:

};