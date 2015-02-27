/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include <iostream>
#include <exception>
using namespace std;

//Hard exeption does casuse game to shutdown
class HardException :public exception{
public:
	HardException(const string m = "HardException") :msg(m){}

	const char* what(){ return msg.c_str(); }
private:
	string msg;
};

//Light exeption does not casuse game to shutdown (for example trying to load a nonexistent texture)
class LightException :public exception{ 
public:
	LightException(const string m = "LightException") :msg(m){}

	const char* what(){ return msg.c_str(); }
private:
	string msg;
};

// TODO(Get this to work)