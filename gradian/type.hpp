/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/
#pragma once

enum unitType {
	GROUND
};
// 2D sprite class, there are multiple ways to define a sprite.
class Type
{
public:
	int maxHP;

	int attack;
	int defence;

	string name;

	unitType type;

	Type(string name, int maxhp, int attack, int defence, unitType type)
	{
		this->name = name;
		this->maxHP = maxhp;
		this->attack = attack;
		this->defence = defence;
		this->type = type;
	}


private:

};