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

void Sprite::setupSprite(glTexture texture, int width, int height, float angle)
{
	this->height = width;
	this->width = height;
	this->angle = angle;
	this->texture = texture;
	this->size = glm::vec2(width, height);
	this->color = glm::vec4(1, 1, 1, 1);

	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::Draw(Shader *s, int x, int y)
{
	glm::mat4 projection = glm::ortho(0.0f, vid_width->toFloat(), vid_height->toFloat(), 0.0f, -1.0f, 1.0f);

	glm::mat4 model;
	glm::vec2 origin = glm::vec2(x, y);
	model = glm::translate(model, glm::vec3(origin, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * this->size.x, 0.5f * this->size.y, 0.0f));
	model = glm::rotate(model, this->angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * this->size.x, -0.5f * this->size.y, 0.0f));

	model = glm::scale(model, glm::vec3(this->size, 1.0f));

	s->Use();
	s->SetMatrix4("model", model);
	s->SetMatrix4("projection", projection);
	s->SetVector4f("spriteColor",this->color);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture.id);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}