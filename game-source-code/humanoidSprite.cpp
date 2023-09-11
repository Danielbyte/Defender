#include "humanoidSprite.h"

HumanoidSprite::HumanoidSprite():
	texture_period{1.0f}
{
	sf::Vector2f dimensions;
	dimensions.x = 8.0f;
	dimensions.y = 12.0f;
	InitialiseEntityOrigin(dimensions);
	loadTextures();
}

void HumanoidSprite::loadTextures()
{
	humanoidLeft1_t.loadFromFile("resources/humanoidleft-1.png");
	humanoidLeft2_t.loadFromFile("resources/humanoidleft-2.png");
	humanoidRight1_t.loadFromFile("resources/humanoidright-1.png");
	humanoidRight2_t.loadFromFile("resources/humanoidright-2.png");
	fallingHumanoid1_t.loadFromFile("resources/falling-humanoid1.png");
	fallingHumanoid2_t.loadFromFile("resources/falling-humanoid2.png");
	fallingHumanoid3_t.loadFromFile("resources/falling-humanoid3.png");
}

void HumanoidSprite::setTexture(std::string direction, std::shared_ptr<StopWatch>& watch, const HumanoidState state)
{
	switch (state)
	{
	case HumanoidState::Walking:
	case HumanoidState::Abducted:
		//load walking textures
		walkingAndAbuction(direction, watch);
		break;

	case HumanoidState::Falling:
		//load falling textures
		break;
	default:
		break;
	}
}

void HumanoidSprite::walkingAndAbuction(std::string direction,std::shared_ptr<StopWatch>& watch)
{
	texture_period = 1.0f;
	auto _time = watch->time_elapsed();

	if (direction == "left")
	{
		if (_time >= 0.0f && _time <= texture_period)
			updateSpriteTexture(humanoidLeft1_t);

		if (_time > texture_period && _time <= 2 * texture_period)
		{
			updateSpriteTexture(humanoidLeft2_t);
			watch->restart();
		}
		return;	
	}

	if (_time >= 0.0f && _time <= texture_period)
		updateSpriteTexture(humanoidRight1_t);

	if (_time > texture_period && 2 * texture_period)
	{
		updateSpriteTexture(humanoidRight2_t);
		watch->restart();
	}
}