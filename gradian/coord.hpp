/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/
#pragma once

enum terrainType
{
	NOTHING,
	GRASS,
	WATER
};

// A location in the 2d gameboard
class Coord
{
public:
	vector<Unit *> units;
	terrainType terrain;
	int x, y;


	Coord(int x, int y, terrainType type)
	{
		this->x = x;
		this->y = y;
		this->terrain = type;

	}

	~Coord()
	{
		for (auto unit : this->units)
		{
			delete unit;
		}
	}

	Result addUnit(Unit *adding)
	{
		if ((std::find(units.begin(), units.end(), adding) != units.end()))
			return Result("Unit already in given area", false);

		units.push_back(adding);
		Result("Unit added to the area", true);
	}

	Result removeUnit(Unit *remove)
	{
		auto unit = std::find(units.begin(), units.end(), remove);
		if (unit != units.end())
			return Result("Unit is not in the area area", false);

		units.erase(unit);
		Result("Unit removed from the area", true);
	}

	string toString()
	{
		return ("X: " + to_string(this->x) + " Y: " + to_string(this->y) + " type: " + to_string(this->terrain));
	}
private:

};