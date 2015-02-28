/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include "gl_shader.hpp"

extern void debugPrint(std::string message);
extern void errorPrint(std::string message);
// Temp move objects tot heir own classes

int initModels();

class GLObject
{
public:
	GLuint VBO = 0, VAO = 0, EBO;
	vector<GLfloat> verticles;
	vector<GLuint> indents;
	Shader *shader;
	glm::vec3 origin;
	GLObject(vector<GLfloat> verts, vector<GLuint> ind, Shader *shader)
	{
		this->verticles = verts;
		this->indents = ind;
		this->shader = shader;


		glGenBuffers(1, &this->VBO);//generate the buffer
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO); //bind the newly generated buffer
		
		GLuint bufferSize = this->verticles.size() * sizeof(this->verticles);
		glBufferData(GL_ARRAY_BUFFER, bufferSize, &this->verticles[0], GL_STATIC_DRAW);//set data to the buffer from verticles

		GLuint sizeOffset = this->verticles.size()/2 * 4;

		glEnableVertexAttribArray(0);//position
		glEnableVertexAttribArray(1);//color
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeOffset);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void draw()
	{
		this->shader->Use();


		GLint offsetUniform = glGetUniformLocation(this->shader->Program, "offset");
		glUniform2f(offsetUniform, 0.5f, 0.5f);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO); //bind the newly generated buffer

		// TODO(Jukki) Cvar or something to control this
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		GLuint numOfTriangles = this->verticles.size() / 8;
		glDrawArrays(GL_TRIANGLES, 0, numOfTriangles);

		glBindVertexArray(0);

		glUseProgram(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};