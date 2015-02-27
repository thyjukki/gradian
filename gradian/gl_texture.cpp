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
	string truePath = (MAINDIR + path); // TODO(Jukki) do this better
	//first check that we havent allready loaded the texture
	for (std::vector<glTexture>::iterator it = gl_textures.begin(); it != gl_textures.end(); ++it)
	{
		if (it->path == truePath)
			return *it;
	}
	//Generate texture ID and load texture data to struct
	glTexture texture;
	texture.path = truePath;

	unsigned char* image = SOIL_load_image(truePath.c_str(), &texture.width, &texture.height, 0, SOIL_LOAD_RGBA);
	if (0 == image)
	{
		throw LightException("ERROR::SOIL::" + truePath + " loading error " + std::string(SOIL_last_result()));
	}

	glGenTextures(1, &texture.id);

	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
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