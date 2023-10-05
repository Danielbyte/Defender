#include "spriteStore.h"

SpriteStore::SpriteStore():
	toTheLeft{false},
	toTheRight{true},
	canDelete{false}
{
}

void SpriteStore::updateSpritePosition(const std::string& entityDirection, const float x_pos,const float y_pos,
	const float miniXpos, const float miniYpos)
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
	miniSprite.setPosition(miniXpos, miniYpos);
	animationSprite.setPosition(x_pos, y_pos);
}

sf::Sprite SpriteStore::getSprite() const
{
	return entitySprite;
}

void SpriteStore::updateSpriteTexture(sf::Texture& texture, sf::Texture& miniTexture)
{
	entitySprite.setTexture(texture);
	miniSprite.setTexture(miniTexture);
}

bool SpriteStore::getIfLeft() const
{
	return toTheLeft;
}

bool SpriteStore::getIfRight() const
{
	return toTheRight;
}

void SpriteStore::InitialiseEntityOrigin(const sf::Vector2f& dimensions, const sf::Vector2f miniDimensions, const sf::Vector2f animationDimensions)
{
	entitySprite.setOrigin(dimensions/2.0f);
	miniSprite.setOrigin(miniDimensions / 2.0f);
	animationSprite.setOrigin(animationDimensions / 2.0f);
}

void SpriteStore::remove()
{
	canDelete = true;
}

bool SpriteStore::needsDeletion() const
{
	return canDelete;
}

sf::Sprite SpriteStore::getMiniSprite() const
{
	return miniSprite;
}

void SpriteStore::updateAnimationSpriteTexture(sf::Texture& animationTexture, sf::Texture& miniTexture)
{
	animationSprite.setTexture(animationTexture);
	miniSprite.setTexture(miniTexture);
}

sf::Sprite SpriteStore::getAnimationSprite() const
{
	return animationSprite;
}