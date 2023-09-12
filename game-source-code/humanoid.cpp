#include "humanoid.h"

Humanoid::Humanoid():
state{HumanoidState::Walking}, //Humanoid initially walking
direction{"unknown"},
xPosition{0.0f},
yPosition{0.0f},
speed{25.0f}
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

std::tuple<float, float> Humanoid::getPosition() const
{
	return { xPosition, yPosition };
}

void Humanoid::updateHumanoid(const float dt, std::shared_ptr<HumanoidSprite>& humanoid_sprite)
{
	if (direction == "right")
		xPosition += speed * dt;

	if (direction == "left")
		xPosition -= speed * dt;

	updateHumanoidSprite(humanoid_sprite);
}

void Humanoid::updateHumanoidSprite(std::shared_ptr<HumanoidSprite>& humanoid_sprite)
{
		switch (state)
		{
		case HumanoidState::Walking:
		case HumanoidState::Abducted:
			humanoid_sprite->setTexture(direction, "Walking",xPosition,yPosition);
			break;
		
		case HumanoidState::Falling:
			humanoid_sprite->setTexture(direction, "Falling", xPosition, yPosition);
			break;

		case HumanoidState::Dead:
			break;
		default:
			break;
		}
}
