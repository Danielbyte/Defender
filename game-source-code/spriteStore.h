#ifndef SPRITESTORE_H
#define SPRITESTORE_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "stopWatch.h"
#include <memory>

class SpriteStore
{
public:
	SpriteStore();
	void updateSpritePosition(const std::string& direction, const float x_pos, const float y_pos,
		const float miniXpos, const float miniYpos);
	void updateSpriteTexture(sf::Texture& texture, sf::Texture& miniTexture);
	void updateAnimationSpriteTexture(sf::Texture& animationTexture, sf::Texture& miniTexture);
	void updateExplosionSpriteTexture(sf::Texture& explosionTexture, sf::Texture& miniTexture);
    sf::Sprite getSprite() const;
	sf::Sprite getMiniSprite() const;
	sf::Sprite getAnimationSprite() const;
	sf::Sprite getExplosionSprite() const;
	virtual void loadTextures() = 0;
	bool getIfLeft() const;
	bool getIfRight() const;
	void InitialiseEntityOrigin(const sf::Vector2f& dimensions, const sf::Vector2f miniDimensios, const sf::Vector2f animationDimensions);
	void remove();
	bool needsDeletion() const;

private:
	bool toTheLeft;
	bool toTheRight;
	sf::Sprite entitySprite;
	sf::Sprite miniSprite; // sprites for mini map
	sf::Sprite animationSprite;
	sf::Sprite explosionSprite;
	bool canDelete;
};
#endif // !SPRITESTORE_H

