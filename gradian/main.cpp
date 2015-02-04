/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

// GL includes
#include "Shader.hpp"

// Common includes
#include "common.hpp"

int glInitWindow();

Gradian gradian;


int main()
{
	bool running = true;
	bool error = false;

	// TODO(Jukki) Error handling if inits fail
	try
	{
		if (!glInitWindow()
			|| !initCvars()
			|| !initInput()
			|| !initShaders()
			|| !initModels()
			|| !initDisplay()
			|| !initText())
			error = true;
	}
	catch (MyException& e){
		errorPrint(e.what());
	}
	catch (std::exception& e)
	{
		errorPrint(e.what());
		error = true;
		//Other errors
	}

	glTexture test = TextureFromFile("awesomeface.png");
	test_object = new Sprite(test, 0, 0, 100, 100);
	test_object2 = new Sprite(test, 100, 100, 200, 200);

	while (running && !error)
	{
		try
		{
			if (!glfwWindowShouldClose(gradian.main_window))
			{
				glfwPollEvents();


				//TODO(Jukki) Well, prety much everything
				renderScene();
				glfwSwapBuffers(gradian.main_window);
			}
			else running = false;
		}
		catch (MyException& e){
			errorPrint(e.what());
		}
		catch (std::exception& e)
		{
			errorPrint(e.what());
			error = true;
			//Other errors
		}
	}

	glfwTerminate();
	return 0;
}