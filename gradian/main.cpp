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

int glInitGL();

Gradian gradian;


int main()
{
	bool running = true;
	bool error = false;

	// TODO(Jukki) Error handling if inits fail
	try
	{
		if (!initCvars() //make sure cvars are loaded first!!!
			|| !initDisplay()
			|| !glInitGL()
			|| !initInput()
			|| !initShaders()
			|| !initModels()
			|| !initDraw()
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

	// Wrap things up and save everything we need to.
	if (!error)
	{
		saveCvars();
	}

	glfwTerminate();
	return 0;
}