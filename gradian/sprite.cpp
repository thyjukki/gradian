/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"

Sprite *test_object;
Sprite *test_object2;

void Sprite::setupSprite(glTexture texture, float x, float y, int width, int height, float angle)
{
	this->height = width;
	this->width = height;
	this->angle = angle;
	this->texture = texture;
	this->origin = glm::vec2(x, y);
	this->size = glm::vec2(width, height);

	GLfloat vertices[] = {
		// Positions	// Colors			// Texture Coords
		0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 	// Top Right
		0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, 	// Bottom Right
		-0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 	// Bottom Left
		-0.5f, 0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f		// Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Sprite::Draw(Shader *s)
{
	glm::mat4 projection = glm::ortho(0.0f, (float)window_width, (float)window_height, 0.0f, -1.0f, 1.0f);


	glm::mat4 model;
	model = glm::translate(model, glm::vec3(this->origin, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, this->angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	s->Use();
	glUniformMatrix4fv(s->modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(s->projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindTexture(GL_TEXTURE_2D, this->texture.id);

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}