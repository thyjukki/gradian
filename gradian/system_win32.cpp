#ifdef WIN32
#include "Windows.h"
#include <string>
int main();

#include "common.hpp"

int WINAPI WinMain (HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	return main();
}

void debugPrint(std::string message)
{
	if (developer->isTrue())
		OutputDebugStringA((message + "\n").c_str());
}

// TODO(Jukki) Make proper error message
void errorPrint(std::string message)
{
	std::string Message = message + "\n";
	OutputDebugStringA(Message.c_str());

	std::wstring widestr = std::wstring(Message.begin(), Message.end());
	LPCWSTR output = widestr.c_str();

	MessageBox(
		NULL,
		output,
		L"Hard Exception",
		MB_ICONEXCLAMATION | MB_OK
		);
}

#endif