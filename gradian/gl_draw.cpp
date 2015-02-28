/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/
#include "common.hpp"

Sprite *mouseCursor;

//-----------------------------------------------------------------------------
// Name: glEnable2D
// Desc: Enabled 2D primitive rendering by setting up the appropriate orthographic
//               perspectives and matrices.
//-----------------------------------------------------------------------------
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
	glTexture cursor = TextureFromFile("Textures/awesomeface.png");
	mouseCursor = new Sprite(cursor, 20, 20);

	return 1;
}