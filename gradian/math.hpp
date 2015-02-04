/*******************************************************************
** This code is part of Gradian game engine
**
** All code is free to use if proper credit is given.
** If you found this code without proper credit please contact me
** Jussi Joki (judejoki@gmail.com)
******************************************************************/

//standard 2d vector, used for example screen origin

#pragma once

class Vec2
{
public:
	Vec2(float i, float j)
	{
		this->i = i;
		this->j = j;
	};
	float i;
	float j;

	glm::vec2 glmVec2()
	{
		return glm::vec2(this->i, this->j);
	}

	glm::vec3 glmVec3()
	{
		return glm::vec3(this->i, this->j, 0);
	}

	glm::vec4 glmVec4()
	{
		return glm::vec4(this->i, this->j, 0, 1);
	}
};