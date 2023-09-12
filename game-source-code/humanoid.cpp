#include "humanoid.h"

Humanoid::Humanoid():
state{HumanoidState::Walking}, //Humanoid initially walking
direction{"unknown"},
xPosition{0.0f},
yPosition{0.0f},
speed{0.9f}
{
	placeHumanoid();
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
			humanoid_sprite->setTexture(direction, "Walking",xPosition,yPosition,humanoid_watch);
			break;
		
		case HumanoidState::Falling:
			humanoid_sprite->setTexture(direction, "Falling", xPosition, yPosition,humanoid_watch);
			break;

		case HumanoidState::Dead:
			break;
		default:
			break;
		}
}

void Humanoid::placeHumanoid()
{
	 yPosition = 580.0f;
     generateXposition();
	 generateDirection();
}

void Humanoid::generateXposition()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	float min = 4.0f;
	float max = 796.0f;
	std::uniform_real_distribution<float>distribution(min, max);

	xPosition = distribution(gen);
}

void Humanoid::generateDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 1;
	int max = 10;
	std::uniform_int_distribution<int>distribution(min, max);
	auto _direction = distribution(gen);

	if (_direction <= 5)
		direction = "right";

	if(_direction > 5)
		direction = "left";
}
