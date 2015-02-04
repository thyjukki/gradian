/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"


map<string, Shader *> shaderList;


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath, GLuint type)
{
	this->type = type;
	// 1. Retrieve the vertex/fragment source code from filePath
	string vertexCode;
	string fragmentCode;
	try
	{
		// Open files
		ifstream vShaderFile(vertexPath);
		ifstream fShaderFile(fragmentPath);
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
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		debugPrint("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
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
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		debugPrint("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
		debugPrint(infoLog);
		debugPrint("\n");
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
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		debugPrint("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
		debugPrint(infoLog);
		debugPrint("\n");
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
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		debugPrint("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
		debugPrint(infoLog);
		debugPrint("\n");
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	modelLoc = glGetUniformLocation(this->Program, "model");
	viewLoc = glGetUniformLocation(this->Program, "view");
	projectionLoc = glGetUniformLocation(this->Program, "projection");
}



int initShaders()
{
	Shader *test = new Shader("../gradian/Shaders/test.vs", "../gradian/Shaders/test.frag", SHADER_2D);

	shaderList["test"] = test;

	return 1;
}