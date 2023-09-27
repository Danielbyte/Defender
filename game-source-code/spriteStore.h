#ifndef SPRITESTORE_H
#define SPRITESTORE_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "stopWatch.h"

class SpriteStore
{
public:
	SpriteStore();
	void updateSpritePosition(const std::string& direction, const float x_pos, const float y_pos);
	void updateSpriteTexture(sf::Texture& texture);
    sf::Sprite getSprite() const;
	virtual void loadTextures() = 0;
	bool getIfLeft() const;
	bool getIfRight() const;
	void InitialiseEntityOrigin(const sf::Vector2f& dimensions);
	void remove();
	bool needsDeletion() const;

private:
	bool toTheLeft;
	bool toTheRight;
	sf::Sprite entitySprite;
	bool canDelete;
};
#endif // !SPRITESTORE_H

