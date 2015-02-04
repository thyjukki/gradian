#ifdef WIN32
#include "Windows.h"
#include <string>
int main();

int WINAPI WinMain (HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	return main();
}

void debugPrint(std::string message)
{
	OutputDebugStringA(message.c_str());
}

// TODO(Jukki) Make proper error message
void errorPrint(std::string message)
{
	OutputDebugStringA(message.c_str());
}

#endif