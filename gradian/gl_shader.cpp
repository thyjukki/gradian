/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"


map<string, Shader *> shaderList;


Shader::Shader(string vertexPath, string fragmentPath, GLuint type, string name)
{
	this->type = type;
	// 1. Retrieve the vertex/fragment source code from filePath
	string vertexCode;
	string fragmentCode;
	try
	{
		// Open files
		ifstream vShaderFile(MAINDIR + vertexPath);
		ifstream fShaderFile(MAINDIR + fragmentPath);
		stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (exception e)
	{
		throw HardException("ERROR::SHADER::" + name + "::FILE_NOT_SUCCESFULLY_READ " + std::string(e.what()));
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);

		throw HardException("ERROR::SHADER::" + name + "::VERTEX::COMPILATION_FAILED (" + (MAINDIR + vertexPath) + ") " + std::string(infoLog));
	}
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);

		throw HardException("ERROR::SHADER::" + name + "::FRAGMENT::COMPILATION_FAILED (" + (MAINDIR + fragmentPath) + ") " + std::string(infoLog));
	}
	// Shader Program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	// Print linking errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);

		throw HardException("ERROR::SHADER::" + name + "::PROGRAM::LINKING_FAILED" + std::string(infoLog));
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	shaderList[name] = this;
}




int initShaders()
{
	new Shader("Shaders/image.vs", "Shaders/image.frag", SHADER_2D, "image");
	new Shader("Shaders/color.vs", "Shaders/color.frag", SHADER_2D, "color"); // TODO(Jukki) we might need this laterz...


	return 1;
}