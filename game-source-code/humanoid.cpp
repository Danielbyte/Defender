#include "humanoid.h"

Humanoid::Humanoid():
state{HumanoidState::Walking}, //Humanoid initially walking
direction{"unknown"},
xPosition{0.0f},
yPosition{0.0f},
speed{0.9f},
abductingLanderId{0},
distance {0.0f}
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

void Humanoid::updateHumanoid(const float dt, std::shared_ptr<HumanoidSprite>& humanoid_sprite,std::shared_ptr<Player>& p)
{
	if (state == HumanoidState::Rescued)
	{
		updateHumanoid(p, humanoid_sprite);
		return;
	}
		

	if (state == HumanoidState::Abducted)
	{
		auto newSpeed = 50.0f; //set to lander speed
		yPosition -= newSpeed * dt;
		updateHumanoidSprite(humanoid_sprite);
		return;
	}
	
	if (state == HumanoidState::Falling)
	{
		auto newSpeed = 50.0f;
		yPosition += newSpeed * dt;
		updateHumanoidSprite(humanoid_sprite);
		return;
	}

	if (direction == "right")
		xPosition += speed * dt;
		

	if (direction == "left")
	    xPosition -= speed * dt;
		
	updateHumanoidSprite(humanoid_sprite);
}

void Humanoid::updateHumanoid(std::shared_ptr<Player>& player, std::shared_ptr<HumanoidSprite>& humanoid_sprite)
{
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	if (xPosition <= xPlayerPos)
		xPosition = xPlayerPos - distance;
	
	if (xPosition > xPlayerPos)
		xPosition = xPlayerPos + distance;

	auto offset = 18.0f;
	yPosition = yPlayerPos + offset;

	updateHumanoidSprite(humanoid_sprite);
}

void Humanoid::updateHumanoidSprite(std::shared_ptr<HumanoidSprite>& humanoid_sprite)
{
		switch (state)
		{
		case HumanoidState::Walking:
		case HumanoidState::Abducted:
		case HumanoidState::Rescued:
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
	float min = -1000.0f;
	float max = 1000.0f;
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

void Humanoid::setToAbducted()
{
	state = HumanoidState::Abducted;
}

unsigned int Humanoid::getAbductingLanderId() const
{
	return abductingLanderId;
}

void Humanoid::setAbductingLanderId(const unsigned int id)
{
	abductingLanderId = id;
}

void Humanoid::setDistance(const float distanceBetween)
{
	auto offset = 0.2f;
	distance = distanceBetween - offset;
}
