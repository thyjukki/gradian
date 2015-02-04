/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include <ft2build.h>
#include FT_FREETYPE_H 

struct Character {
	GLuint     textureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

extern std::map<GLchar, Character> Characters;

extern int initText();

extern void RenderText(Shader *s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);