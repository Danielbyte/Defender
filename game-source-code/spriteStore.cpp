#include "spriteStore.h"

SpriteStore::SpriteStore()
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
}