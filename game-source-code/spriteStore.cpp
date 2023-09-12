#include "spriteStore.h"

SpriteStore::SpriteStore():
	toTheLeft{false},
	toTheRight{true},
	canDelete{false}
{
}

void SpriteStore::updateSpritePosition(const std::string& entityDirection, const float x_pos,const float y_pos)
{
	if (entityDirection == "right")
	{
		toTheRight = true;
		toTheLeft = false;
	}

	if (entityDirection == "left")
	{
		toTheLeft = true;
		toTheRight = false;
	}

	entitySprite.setPosition(x_pos, y_pos);
}

sf::Sprite SpriteStore::getSprite() const
{
	return entitySprite;
}

void SpriteStore::updateSpriteTexture(sf::Texture& texture)
{
	entitySprite.setTexture(texture);
}

bool SpriteStore::getIfLeft() const
{
	return toTheLeft;
}

bool SpriteStore::getIfRight() const
{
	return toTheRight;
}

void SpriteStore::InitialiseEntityOrigin(const sf::Vector2f& dimensions)
{
	entitySprite.setOrigin(dimensions/2.0f);
}

void SpriteStore::remove()
{
	canDelete = true;
}

bool SpriteStore::needsDeletion() const
{
	return canDelete;
}