#include "playerLaserSprite.h"

PlayerLaserSprite::PlayerLaserSprite()
{}

PlayerLaserSprite::PlayerLaserSprite(const std::string& direction, const std::string& color)
{
	loadTextures();
	sf::Vector2f dimensions;
	dimensions.x = 100.0f;
	dimensions.y = 1.0f;
	InitialiseEntityOrigin(dimensions);
}

void PlayerLaserSprite::loadTextures()
{
	redRight_t.loadFromFile("resources/right-red-laser.png");
	redLeft_t.loadFromFile("resources/left-red-laser.png");
	greenRight_t.loadFromFile("resources/right-green-laser.png");
	greenLeft_t.loadFromFile("resources/left-green-laser.png");
	blueRight_t.loadFromFile("resources/right-blue-laser.png");
	blueLeft_t.loadFromFile("resources/left-blue-laser.png");
}

void PlayerLaserSprite::setTexture(const std::string& direction, const std::string& color)
{
	if (direction == "right")
	{
		if (color == "green")
			updateSpriteTexture(greenRight_t);
		
		if (color == "red")
			updateSpriteTexture(redRight_t);

		if (color == "blue")
			updateSpriteTexture(blueRight_t);
	}

	if (direction == "left")
	{
		if (color == "green")
			updateSpriteTexture(greenLeft_t);

		if (color == "red")
			updateSpriteTexture(redLeft_t);

		if (color == "blue")
			updateSpriteTexture(blueLeft_t);
	}
}

sf::Texture PlayerLaserSprite::getTexture()
{
	return greenRight_t;
}