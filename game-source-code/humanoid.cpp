#include "humanoid.h"

Humanoid::Humanoid():
state{HumanoidState::Walking}, //Humanoid initially walking
direction{"unknown"},
xPosition{0.0f},
yPosition{0.0f}
{}

Humanoid::Humanoid(const float initXpos, const float initYpos, std::string _direction) :
	state{ HumanoidState::Walking }
{
	direction = _direction;
	xPosition = initXpos;
	yPosition = initYpos;
}

HumanoidState Humanoid::getHumanoidState() const
{
	return state;
}

void Humanoid::setHumanoidState(const HumanoidState _state)
{
	state = _state;
}

std::string Humanoid::getHumanoidDirection() const
{
	return direction;
}