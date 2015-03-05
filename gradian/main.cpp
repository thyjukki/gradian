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


void testGame()
{
	try
	{
		GameBoard *board = loadMap("Maps/test.gmf");

		if (board->getCoord(1, 1))
			debugPrint(board->getCoord(1, 1)->toString());

		if (board->getCoord(2, 2))
			debugPrint(board->getCoord(2, 2)->toString());

		delete board;
	}
	catch (HardException& e){
		errorPrint(e.what());
	}
	catch (LightException& e){
		errorPrint(e.what());
	}





}


int main()
{
	bool running = true;
	bool error = false;

	try
	{
		initCvars(); // And then set up cvars!
		initConsole(); // We firs load up console,
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
	double lastFrameTime = lastTime;
	int nbFrames = 0;


	//testGame();

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
				gradian.deltaTime = currentTime - lastFrameTime;
				lastFrameTime = currentTime;
				nbFrames++;
				if (currentTime - lastTime >= 1.0){ // If last prinf() was more than 1 sec ago
					// printf and reset timer
					debugPrint(to_string(1000.0 / double(nbFrames)) + " ms/frame, " + to_string(nbFrames) + " FPS");
					nbFrames = 0;
					lastTime += 1.0;
				}
//#endif

				parseGameInput();

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