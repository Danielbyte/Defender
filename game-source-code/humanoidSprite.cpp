#include "humanoidSprite.h"

HumanoidSprite::HumanoidSprite():
	texture_period{0.5f}
{
	sf::Vector2f dimensions;
	dimensions.x = 6.0f;
	dimensions.y = 16.0f;
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

void HumanoidSprite::setTexture(std::string direction, const std::string state, float xPos, float yPos,
	std::shared_ptr<StopWatch>humanoid_watch)
{
	if (state == "Walking" || state == "Abducted")
	{
		walkingAndAbuction(direction,humanoid_watch);
		updateSpritePosition(direction, xPos, yPos);
		return;
	}

	if (state == "Falling")
	{
		falling(direction);
		updateSpritePosition(direction, xPos, yPos);
	}
}

void HumanoidSprite::walkingAndAbuction(std::string direction, std::shared_ptr<StopWatch>humanoid_watch)
{
	texture_period = 1.101f;
	
	auto _time = humanoid_watch->time_elapsed();
	if (_time > 2 * texture_period)
		humanoid_watch->restart();
	
	if (direction == "left")
	{
		if (_time >= 0.0f && _time <= texture_period)
			updateSpriteTexture(humanoidLeft1_t);

		if (_time > texture_period && _time <= 2 * texture_period)
		{
			updateSpriteTexture(humanoidLeft2_t);
			//humanoid_watch->restart();
		}
		return;	
	}

	if (direction == "right")
	{
		if (_time >= 0.0f && _time <= texture_period)
			updateSpriteTexture(humanoidRight1_t);

		if (_time > texture_period && _time <= 2 * texture_period)
		{
			updateSpriteTexture(humanoidRight2_t);
			//humanoid_watch->restart();
		}
		return;
	}
}

void HumanoidSprite::falling(std::string direction)
{
	/*
	texture_period = 1.0f;
	auto _time = humanoid_watch->time_elapsed();

	if (_time >= 0.0f && _time <= texture_period)
		updateSpriteTexture(fallingHumanoid1_t);

	if (_time > texture_period && _time <= 2 * texture_period)
	    updateSpriteTexture(fallingHumanoid2_t);
	
	if (_time > 2 * texture_period && _time <= 3 * texture_period)
	{
		updateSpriteTexture(humanoidRight1_t);
		humanoid_watch->restart();
	}	*/
}