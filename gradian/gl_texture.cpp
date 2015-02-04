/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/
#include "common.hpp"

#include "SOIL.h"

vector<glTexture> gl_textures;

glTexture TextureFromFile(string path)
{

	//first check that we havent allready loaded the texture
	for (std::vector<glTexture>::iterator it = gl_textures.begin(); it != gl_textures.end(); ++it)
	{
		if (it->path == path)
			return *it;
	}
	//Generate texture ID and load texture data to struct
	glTexture texture;
	texture.path = path;

	glGenTextures(1, &texture.id);

	unsigned char* image = SOIL_load_image(path.c_str(), &texture.width, &texture.height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	texture.type = normal; // TODO(Jukki) diferent texture types maybe????

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	gl_textures.push_back(texture);
	return texture;
}