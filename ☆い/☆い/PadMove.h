#pragma once

#include "MyGame/My/Move.h"

class PadMove : public Move
{
private:
public:
	PadMove(Point &apPos, float &afSpd)
		: Move(apPos, afSpd)
	{

	}
	virtual ~PadMove()
	{

	}
	virtual void Update() override
	{
		auto &pad = JoyPad::GetState(0);
		if (pad->Axis(JoyPad::Stick::STK_LEFT) == Vector2::zero) return;
		Pos().x += pad->Axis(JoyPad::Stick::STK_LEFT).GetX() * Spd();
		Pos().y += pad->Axis(JoyPad::Stick::STK_LEFT).GetY() * Spd();
	}
};