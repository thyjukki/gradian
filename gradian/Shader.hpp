#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include <GL/glew.h>
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern void debugPrint(string message);
extern void errorPrint(string message);


#define SHADER_3D 1
#define SHADER_2D 2

class Shader
{
public:

	GLuint Program;
	GLuint type;
	// Constructor generates the shader on the fly
	Shader(string vertexPath, string fragmentPath, GLuint type, string name);
	// Uses the current shader
	void Use() { glUseProgram(this->Program); }

	void SetFloat(const GLchar *name, GLfloat value)
	{
		glUniform1f(glGetUniformLocation(this->Program, name), value);
	}
	void SetInteger(const GLchar *name, GLint value)
	{
		glUniform1i(glGetUniformLocation(this->Program, name), value);
	}
	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y)
	{
		glUniform2f(glGetUniformLocation(this->Program, name), x, y);
	}
	void SetVector2f(const GLchar *name, glm::vec2 value)
	{
		glUniform2f(glGetUniformLocation(this->Program, name), value.x, value.y);
	}
	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
	{
		glUniform3f(glGetUniformLocation(this->Program, name), x, y, z);
	}
	void SetVector3f(const GLchar *name, glm::vec3 value)
	{
		glUniform3f(glGetUniformLocation(this->Program, name), value.x, value.y, value.z);
	}
	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		glUniform4f(glGetUniformLocation(this->Program, name), x, y, z, w);
	}
	void SetVector4f(const GLchar *name, glm::vec4 value)
	{
		glUniform4f(glGetUniformLocation(this->Program, name), value.x, value.y, value.z, value.w);
	}
	void SetMatrix4(const GLchar *name, glm::mat4 matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(this->Program, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
};
