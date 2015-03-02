/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/
#pragma once


// 2D Game board which contains all the coords of the game
class GameBoard
{
public:
	int width, height;
	string name;
	vector<Coord *> grid;

	GameBoard(int x, int y, string name);

	~GameBoard();


	Coord *getCoord(int X, int Y);

	void setCoord(int X, int Y, terrainType type);

	bool checkIfDone();
private:

};

GameBoard *loadMap(string path);

void unloadMap();
void setupMap(string map);