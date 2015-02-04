/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/


enum texType {
	normal
};

struct glTexture {

	// Textures id and type
	GLuint id;
	texType type;

	// Path to texture
	string path;

	// Textures basic info
	int width;
	int height;
};


glTexture TextureFromFile(string path);