/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/
#include "common.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

glTexture char_data;
FT_Face face;
GLuint textVBO, textVAO;

int initText()
{

	char_data = TextureFromFile("Textures/charset.tga");
	
	GLfloat			frow, fcol, size;
	frow = (GLfloat)(5*0.0625);
	fcol = (GLfloat)(5*0.0625);
	size = (GLfloat)(0.0625);
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, fcol, frow + size,
		1.0f, 0.0f, fcol + size, frow,
		0.0f, 0.0f, fcol, frow,

		0.0f, 1.0f, fcol, frow + size,
		1.0f, 1.0f, fcol + size, frow + size,
		1.0f, 0.0f, fcol + size, frow
	};

	glGenVertexArrays(1, &textVAO);
	glGenBuffers(1, &textVBO);

	glBindVertexArray(textVAO);

	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 1;
}

/*void render_text(const char *text, float x, float y, float sx, float sy) {
// TODO(Jukki) text drwawing function here!
}*/



// TODO(Jukki) Thease are loaned from quake, please make your own later.

/*
================
Draw_CharacterQuad -- johnfitz -- seperate function to spit out verts
================
*/
void Draw_CharacterQuad(int x, int y, int sizeX, int sizeY, glm::vec4 color, char num)
{
	GLfloat				row, col;
	GLfloat			frow, fcol, size;

	row = (GLfloat)(num >> 4);
	col = (GLfloat)(num & 15);

	frow = (GLfloat)(row*0.0625);
	fcol = (GLfloat)(col*0.0625);
	size = (GLfloat)(0.0625);

	/*debugPrint("frow " + to_string(frow) + " fcol " + to_string(fcol));
	glTexCoord2f(fcol, frow);
	glVertex2f((GLfloat)x, (GLfloat)y);
	glTexCoord2f(fcol + size, frow);
	glVertex2f((GLfloat)x + (GLfloat)8.0, (GLfloat)y);
	glTexCoord2f(fcol + size, fcol, frow + size);
	glVertex2f((GLfloat)x + (GLfloat)8.0, (GLfloat)y + (GLfloat)8.0);
	glTexCoord2f(fcol, frow + size);
	glVertex2f((GLfloat)x, (GLfloat)y + (GLfloat)8.0);*/


	glm::mat4 projection = glm::ortho(0.0f, vid_width->toFloat(), vid_height->toFloat(), 0.0f, -1.0f, 1.0f);

	glm::mat4 model;
	glm::vec2 origin = glm::vec2(x, y);
	model = glm::translate(model, glm::vec3(origin, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * sizeX, 0.5f * sizeY, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * sizeX, -0.5f * sizeY, 0.0f));

	model = glm::scale(model, glm::vec3(glm::vec2(sizeX, sizeY), 1.0f));

	Shader *s = shaderList["image"];
	s->Use();
	s->SetMatrix4("model", model);
	s->SetMatrix4("projection", projection);
	s->SetVector4f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, char_data.id);

	glBindVertexArray(textVAO);
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, fcol, frow + size,
		1.0f, 0.0f, fcol + size, frow,
		0.0f, 0.0f, fcol, frow,

		0.0f, 1.0f, fcol, frow + size,
		1.0f, 1.0f, fcol + size, frow + size,
		1.0f, 0.0f, fcol + size, frow
	};
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/*
================
Draw_String -- johnfitz -- modified to call Draw_CharacterQuad
Modified by Jukki to work
TODO(Jukki) this whole thing needs to be eventualy replaced
================
*/
void render_text(int x, int y, int sizeX, int sizeY, glm::vec4 color, string s)
{
	if (y <= -8)
		return;			// totally off screen

	const char *str = s.c_str();

	while (*str)
	{
		if (*str != 32) //don't waste verts on spaces
			Draw_CharacterQuad(x, y, sizeX, sizeY, color, *str);
		str++;
		x += sizeX;
	}

}