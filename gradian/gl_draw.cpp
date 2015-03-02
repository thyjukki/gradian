/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/
#include "common.hpp"

Sprite *mouseCursor;

GLuint rectVAO;
int rectVertexSetup()
{
	GLuint vbo;
	GLfloat vertices[] = {
		// Pos
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &vbo);

	glBindVertexArray(rectVAO);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
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
Draw_Rectangle -- drawa rectangle
================
*/
void Draw_Rectangle(int x, int y, int width, int height, glm::vec4 color, float angle)
{
	glm::mat4 projection = glm::ortho(0.0f, vid_width->toFloat(), vid_height->toFloat(), 0.0f, -1.0f, 1.0f);

	glm::mat4 model;
	glm::vec2 origin = glm::vec2(x, y);
	model = glm::translate(model, glm::vec3(origin, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * width, 0.5f * height, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * width, -0.5f * height, 0.0f));

	model = glm::scale(model, glm::vec3(glm::vec2(width, height), 1.0f));

	Shader *s = shaderList["color"];
	s->Use();
	s->SetMatrix4("model", model);
	s->SetMatrix4("projection", projection);
	s->SetVector4f("spriteColor", color);

	glBindVertexArray(rectVAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}



void drawCursor()
{
	mouseCursor->Draw(shaderList["image"], (int)cursorLocation.x, (int)cursorLocation.y);
	//test_object->Draw(shaderList["image"], 0, 0);
}


//-----------------------------------------------------------------------------
// Name: glEnable2D
// Desc: Enabled 2D primitive rendering by setting up the appropriate orthographic
//               perspectives and matrices.
//-----------------------------------------------------------------------------
void glEnable2D(void)
{
	GLint iViewport[4];

	// Get a copy of the viewport
	glGetIntegerv(GL_VIEWPORT, iViewport);

	// Save a copy of the projection matrix so that we can restore it 
	// when it's time to do 3D rendering again.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// Set up the orthographic projection
	glOrtho(iViewport[0], iViewport[0] + iViewport[2],
		iViewport[1] + iViewport[3], iViewport[1], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// Make sure depth testing and lighting are disabled for 2D rendering until
	// we are finished rendering in 2D
	glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
}


//-----------------------------------------------------------------------------
// Name: glDisable2D
// Desc: Disables 2D rendering and restores the previous matrix and render states
//               before they were modified.
//-----------------------------------------------------------------------------
void glDisable2D(void)
{
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


//-----------------------------------------------------------------------------
// Name: renderScene
// Desc: Render the whole game, one bit a time.
//-----------------------------------------------------------------------------
void renderScene()
{
	glClearColor(0.1f, 0.2f, 0.2f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//beging 2d drawing
	glEnable2D();

	//test_object2->Draw(shaderList["image"], 0, 0);
	//test_object->Draw(shaderList["image"], 100, 100);
	//End 2d drawing
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	render_text(100, 100, 10, 10, glm::vec4(1, 1, 1, 1), "This is a test string to test if the string is awesome");
	render_text(100, 110, 10, 10, glm::vec4(0, 0, 1, 1), "It also supports different colors!");
	render_text(100, 120, 20, 20, glm::vec4(1, 0, 1, 1), "And different sizes!");

	drawConsole();

	drawCursor();

	glDisable2D();
}


//-----------------------------------------------------------------------------
// Name: initDraw
// Desc: Render the whole game, one bit a time.
//-----------------------------------------------------------------------------
int initDraw()
{
	rectVertexSetup();
	glTexture cursor = TextureFromFile("Textures/awesomeface.png");
	mouseCursor = new Sprite(cursor, 20, 20);

	return 1;
}