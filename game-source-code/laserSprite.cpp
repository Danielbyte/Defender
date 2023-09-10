#include "laserSprite.h"

LaserSprite::LaserSprite()
{}

LaserSprite::LaserSprite(const std::string& direction, const std::string& color)
{
	loadTextures();
	sf::Vector2f dimensions;
	dimensions.x = 100.0f;
	dimensions.y = 2.0f;
	InitialiseEntityOrigin(dimensions);
}

void LaserSprite::loadTextures()
{
	redRight_t.loadFromFile("resources/right-red-laser.png");
	redLeft_t.loadFromFile("resources/left-red-laser.png");
	greenRight_t.loadFromFile("resources/right-green-laser.png");
	greenLeft_t.loadFromFile("resources/left-green-laser.png");
	blueRight_t.loadFromFile("resources/right-blue-laser.png");
	blueLeft_t.loadFromFile("resources/left-blue-laser.png");
}

void LaserSprite::setTexture(const std::string& direction, const std::string& color)
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

sf::Texture LaserSprite::getTexture()
{
	return greenRight_t;
}