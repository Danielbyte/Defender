#include "humanoid.h"

Humanoid::Humanoid():
state{HumanoidState::Walking} //Humanoid initially walking
{}

HumanoidState Humanoid::getHumanoidState() const
{
	return state;
}

void Humanoid::setHumanoidState(const HumanoidState _state)
{
	state = _state;
}
