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

class MyException :public exception{
public:
	MyException(const string m = "my custom exception") :msg(m){}
	//~MyException(void);
	const char* what(){ return msg.c_str(); }
private:
	string msg;
};

// TODO(Get this to work)