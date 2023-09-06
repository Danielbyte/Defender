#include "spriteStore.h"

SpriteStore::SpriteStore():
	playerFacingLeft{false},
	playerFacingRight{true}
{
	loadPlayerShipSprites();
}

void SpriteStore::loadPlayerShipSprites()
{
	sf::Vector2f spaceShipDimensions;
	spaceShipDimensions.x = 50.0f;
	spaceShipDimensions.y = 20.0f;
	playerShip_lT.loadFromFile("resources/spaceship-left.png");
	playerShip_rT.loadFromFile("resources/spaceship-right.png");

	playerShip_lS.setTexture(playerShip_lT);
	playerShip_lS.setOrigin(spaceShipDimensions / 2.0f);
	playerShip_rS.setTexture(playerShip_rT);
	playerShip_rS.setOrigin(spaceShipDimensions / 2.0f);
}

void SpriteStore::updatePlayerShipSprite(const std::string& shipDirection, const float& x_pos,const float& y_pos)
{
	if (shipDirection == "right")
	{
		playerFacingRight = true;
		playerFacingLeft = false;
	}

	if (shipDirection == "left")
	{
		playerFacingLeft = true;
		playerFacingRight = false;
	}

	playerShip_rS.setPosition(x_pos, y_pos);
	playerShip_lS.setPosition(x_pos, y_pos);
}

sf::Sprite SpriteStore::getPlayerShipSprite()
{
	if (playerFacingLeft)
	{
		return playerShip_lS;
	}

	if (playerFacingRight)
	{
		return playerShip_rS;
	}
}
