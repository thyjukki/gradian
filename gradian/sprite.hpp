/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/
#pragma once


// 2D sprite class, there are multiple ways to define a sprite.
class Sprite
{
public:

	int width;
	int height;
	float angle;
	glm::vec2 origin;
	glm::vec2 size;

	glTexture texture;


	Sprite(glTexture texture)
	{
		setupSprite(texture, 0, 0, texture.width, texture.height, 0.0);
	}
	Sprite(glTexture texture, float x, float y)
	{
		setupSprite(texture, x, y, texture.width, texture.height, 0.0);
	}
	Sprite(glTexture texture, float x, float y, float angle)
	{
		setupSprite(texture, x, y, texture.width, texture.height, angle);
	}
	Sprite(glTexture texture, float x, float y, int width, int height)
	{
		setupSprite(texture, x, y, width, height, 0.0);
	}
	Sprite(glTexture texture, float x, float y, int width, int height, float angle)
	{
		setupSprite(texture, x, y, width, height, angle);

	}

	void Draw(Shader *s);

private:
	GLuint VBO, VAO, EBO;
	void setupSprite(glTexture texture, float x, float y, int width, int height, float angle);
};


extern Sprite *test_object;
extern Sprite *test_object2;