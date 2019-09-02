#pragma once

#include "MyGame/My/Move.h"

class Stop : public Move
{
private:
public:
	Stop(Point &apPos, float &afSpd)
		: Move(apPos, afSpd)
	{

	}
	virtual ~Stop()
	{

	}
	virtual void Update() override
	{
		/*not move*/
	}
};