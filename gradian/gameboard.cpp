/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

#include "common.hpp"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


using namespace std;
using namespace boost;


string currentMap;
GameBoard *currentBoard;

enum blocks
{
	EMPTY,
	INFO,
	TEXTURES,
	TILES
};

GameBoard::GameBoard(int x, int y, string name) : grid(x*y)
{
	this->width = x;
	this->height = y;
	this->name = name;
}

GameBoard::~GameBoard()
{
	for (auto coord : this->grid)
	{
		delete coord;
	}
}


Coord *GameBoard::getCoord(int X, int Y)
{
	if (X < 1 || X > this->width || Y < 0 || Y > this->height)
	{
		throw LightException("WARNING::getCoord Out of bounds (x = " + to_string(X) + ", y = " + to_string(Y) + ")");
		return 0;
	}
	int y = Y - 1;
	int x = X - 1;
	int index = y*width + x;
	return this->grid[index];
}

void GameBoard::setCoord(int X, int Y, terrainType type)
{
	if (X < 1 || X > this->width || Y < 0 || Y > this->height)
	{
		throw LightException("WARNING::setCoord Out of bounds (x = " + to_string(X) + ", y = " + to_string(Y) + ")");
		return;
	}
	Coord *coord = new Coord(X, Y, type);
	int y = Y - 1;
	int x = X - 1;
	int index = y*width + x;

	grid[index] = coord;
}

bool GameBoard::checkIfDone()
{
	for (auto coord : this->grid)
	{
		if (!coord)
			return false;
	}
	return true;
}


/*
loadMap

Loads a map and initializes the game board by setting up the coords.

returns null if map loading failed
*/
GameBoard *loadMap(string path)
{
	std::ifstream infile(path);

	// Required info
	string name;
	int width;
	int height;
	vector<string> texturePaths;

	vector<string> tiles;

	bool infoBlock = false;
	bool textureBlock = false;
	bool tilesBlock = false;
	
	blocks currentlyProcessing = EMPTY;
	try {
		for (string line; getline(infile, line);)
		{
			trim(line);


			if (line == "#info")
				currentlyProcessing = INFO;
			else if (line == "#textures")
				currentlyProcessing = TEXTURES;
			else if (line == "#tiles")
				currentlyProcessing = TILES;
			 else if (line[0] == '#')
				currentlyProcessing = EMPTY;

			vector<string> entry;

			if (currentlyProcessing == TILES)
			{
				boost::split(entry, line, boost::is_any_of("-"));

				if (entry.size() == 4)
				{
					string X = entry[0];
					string Y = entry[1];
					string TEXTURE = entry[2];
					string TYPE = entry[3];
					trim(X);
					trim(Y);
					trim(TEXTURE);
					trim(TYPE);

					int x = boost::lexical_cast<int>(X);
					int y = boost::lexical_cast<int>(Y);
					int t1 = boost::lexical_cast<int>(TEXTURE);
					int t2 = boost::lexical_cast<int>(TYPE);

					tiles.push_back(to_string(x) + "-" + to_string(y) + "-" + to_string(t1) + "-" + to_string(t2));
				}
			}
			else if (currentlyProcessing != EMPTY)
			{
				boost::split(entry, line, boost::is_any_of("="));

				if (entry.size() == 2)
				{
					string key = entry[0];
					string value = entry[1];
					trim(key);
					trim(value);

					if (currentlyProcessing == INFO)
					{
						if (key == "x")
						{
							width = boost::lexical_cast<int>(value);
						}
						if (key == "y")
						{
							height = boost::lexical_cast<int>(value);
						}
						if (key == "name")
						{
							name = value;
						}
					}
					if (currentlyProcessing == TEXTURES)
					{
						int index = boost::lexical_cast<int>(key)-1;
						if (index >= 0)
							texturePaths.insert(texturePaths.begin() + index, value);
					}
				}
			}
		}

		if (width == 0 || height == 0 || name == "")
			throw LightException("WARNING::GAMEBOARD::LOADMAP Corrupted map file, info block missing data");

		if (texturePaths.empty())
			throw LightException("WARNING::GAMEBOARD::LOADMAP Corrupted map file, texture block missing data");

		if (tiles.empty())
			throw LightException("WARNING::GAMEBOARD::LOADMAP Corrupted map file, texture block missing data");

		GameBoard *board = new GameBoard(width, height, name);


		// TODO(Jukki) Implement texture loading here.

		for (auto tile : tiles)
		{
			vector<string> tileData;
			boost::split(tileData, tile, boost::is_any_of("-"));

			if (tileData.size() != 4)
				throw LightException("WARNING::GAMEBOARD::LOADMAP Corrupted map file, bad data present in tile processing");

			string X = tileData[0];
			string Y = tileData[1];
			string TEXTURE = tileData[2];
			string TYPE = tileData[3];
			trim(X);
			trim(Y);
			trim(TEXTURE);
			trim(TYPE);

			int x = boost::lexical_cast<int>(X);
			int y = boost::lexical_cast<int>(Y);
			int texture = boost::lexical_cast<int>(TEXTURE);
			int type = boost::lexical_cast<int>(TYPE);

			board->setCoord(x, y, (terrainType)type);
		}

		if (!board->checkIfDone())
			throw LightException("WARNING::GAMEBOARD::LOADMAP Corrupted map file, tiles missing from map");

		return board;

	}
	catch (HardException& e){
		errorPrint(e.what());
	}
	catch (LightException& e){
		debugPrint(e.what());
	}
	catch (boost::bad_lexical_cast const&) {
		debugPrint("WARNING::GAMEBOARD::LOADMAP Corrupted map file, entry not numerical value");
	}
	catch (std::exception& e)
	{
		errorPrint(e.what());
	}

	return NULL;
}

void unloadMap()
{
	// TODO(Jukki) We might need to do more here? (inform rest of the players about disconnet, unload ai, unload textures?? and so on)
	delete currentBoard;
	gradian.state = MENU;
}

void setupMap(string map)
{
	gradian.state = LOADING;

	string path = MAINDIR + "Maps/" + map + ".gmf";

	ifstream f(path.c_str());
	if (f.good()) {
		f.close();
		Con_Print("Loading map " + path);
	}
	else {
		f.close();
		Con_Print("Could not find " + path);
		return;
	}

	GameBoard *board = loadMap(path);

	if (board)
	{
		currentBoard = board;
		gradian.state = GAME;
		Con_Print("Map " + map + " loaded");
		gradian.consoleActive = false;
	}
}