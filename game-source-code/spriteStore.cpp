#include "spriteStore.h"

SpriteStore::SpriteStore():
	toTheLeft{false},
	toTheRight{true}
{}

void SpriteStore::updateSpritePosition(const std::string& shipDirection, const float& x_pos,const float& y_pos)
{
	if (shipDirection == "right")
	{
		toTheRight = true;
		toTheLeft = false;
	}

	if (shipDirection == "left")
	{
		toTheLeft = true;
		toTheRight = false;
	}

	entitySprite.setPosition(x_pos, y_pos);
	entitySprite.setPosition(x_pos, y_pos);
}

sf::Sprite SpriteStore::getSprite() const
{
	return entitySprite;
}