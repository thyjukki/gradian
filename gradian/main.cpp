/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

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
		initCvars(); //make sure cvars are loaded first!!!
		initDisplay();
		glInitGL();
		initInput();
		initShaders();
		initModels();
		initDraw();
		initText();
	}
	catch (HardException& e){
		errorPrint(e.what());
		error = true;
	}
	catch (LightException& e){
		debugPrint(e.what());
	}
	catch (std::exception& e)
	{
		errorPrint(e.what());
		error = true;
		//Other errors
	}

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	while (running && !error)
	{
		try
		{
			if (!glfwWindowShouldClose(gradian.main_window))
			{
				glfwPollEvents();

//#ifdef _DEBUG //T TODO(Jukki) Need to fix the problem with debug mode
				// Measure speed
				double currentTime = glfwGetTime();
				nbFrames++;
				if (currentTime - lastTime >= 1.0){ // If last prinf() was more than 1 sec ago
					// printf and reset timer
					debugPrint(to_string(1000.0 / double(nbFrames)) + " ms/frame, " + to_string(nbFrames) + " FPS");
					nbFrames = 0;
					lastTime += 1.0;
				}
//#endif

				// TODO(Jukki) Well, prety much everything
				renderScene();
				glfwSwapBuffers(gradian.main_window);
			}
			else running = false;
		}
		catch (HardException& e){
			errorPrint(e.what());
			error = true;
		}
		catch (LightException& e){
			debugPrint(e.what());
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