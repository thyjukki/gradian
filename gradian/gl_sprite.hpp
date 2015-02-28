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
	glm::vec2 size;
	glm::vec4 color;

	glTexture texture;


	Sprite(glTexture texture)
	{
		setupSprite(texture, texture.width, texture.height, 0.0);
	}
	Sprite(glTexture texture, float angle)
	{
		setupSprite(texture, texture.width, texture.height, angle);
	}
	Sprite(glTexture texture, int width, int height)
	{
		setupSprite(texture, width, height, 0.0);
	}
	Sprite(glTexture texture, int width, int height, float angle)
	{
		setupSprite(texture, width, height, angle);

	}

	void Draw(Shader *s, int x, int y);

private:
	GLuint VBO, VAO, EBO;
	bool initialized;
	void setupSprite(glTexture texture, int width, int height, float angle);
};


extern Sprite *test_object;
extern Sprite *test_object2;