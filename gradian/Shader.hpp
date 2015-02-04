#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include <GL/glew.h>

extern void debugPrint(string message);
extern void errorPrint(string message);


#define SHADER_3D 1
#define SHADER_2D 2

class Shader
{
public:
	GLuint modelLoc;
	GLuint viewLoc;
	GLuint projectionLoc;

	GLuint Program;
	GLuint type;
	// Constructor generates the shader on the fly
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint type);
	// Uses the current shader
	void Use() { glUseProgram(this->Program); }
};
