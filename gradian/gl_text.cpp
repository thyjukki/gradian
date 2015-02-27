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
int initText()
{

	char_data = TextureFromFile("Textures/charset.png");
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
void Draw_CharacterQuad(int x, int y, char num)
{
	GLfloat				row, col;
	GLfloat			frow, fcol, size;

	row = (GLfloat)(num >> 4);
	col = (GLfloat)(num & 15);

	frow = (GLfloat)(row*0.0625);
	fcol = (GLfloat)(col*0.0625);
	size = (GLfloat)(0.0625);

	glTexCoord2f(fcol, frow);
	glVertex2f((GLfloat)x, (GLfloat)y);
	glTexCoord2f(fcol + size, frow);
	glVertex2f((GLfloat)x + (GLfloat)8.0, (GLfloat)y);
	glTexCoord2f(fcol + size, frow + size);
	glVertex2f((GLfloat)x + (GLfloat)8.0, (GLfloat)y + (GLfloat)8.0);
	glTexCoord2f(fcol, frow + size);
	glVertex2f((GLfloat)x, (GLfloat)y + (GLfloat)8.0);
}

/*
================
Draw_String -- johnfitz -- modified to call Draw_CharacterQuad
================
*/
void render_text(int x, int y, string s)
{
	if (y <= -8)
		return;			// totally off screen

	const char *str = s.c_str();
	glBindTexture(GL_TEXTURE_2D, char_data.id);
	glBegin(GL_QUADS);

	while (*str)
	{
		if (*str != 32) //don't waste verts on spaces
			Draw_CharacterQuad(x, y, *str);
		str++;
		x += 8;
	}

	glEnd();
}