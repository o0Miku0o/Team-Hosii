#pragma once

#include "My.h"

class Move
{
private:
	Point &pPosRef;
	float &fSpdRef;
public:
	Move(Point &apPos, float &afSpd)
		: pPosRef(apPos)
		, fSpdRef(afSpd)
	{

	}
	virtual ~Move()
	{

	}
	Point &Pos() const
	{
		return pPosRef;
	}
	float &Spd() const
	{
		return fSpdRef;
	}
	virtual void Update() = 0;
};