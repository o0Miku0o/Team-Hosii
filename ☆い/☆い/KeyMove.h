#pragma once

#include "MyGame/My/Move.h"

class KeyMove : public Move
{
private:
public:
	KeyMove(Point &apPos, float &afSpd)
		: Move(apPos, afSpd)
	{

	}
	virtual ~KeyMove()
	{

	}
	virtual void Update() override
	{
		auto &kb = KB::GetState();
		if (kb->On('W'))
		{
			Pos().y -= Spd();
		}
		if (kb->On('S'))
		{
			Pos().y += Spd();
		}
		if (kb->On('A'))
		{
			Pos().x -= Spd();
		}
		if (kb->On('D'))
		{
			Pos().x += Spd();
		}
	}
};