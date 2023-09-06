#ifndef SPRITESTORE_H
#define SPRITESTORE_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class SpriteStore
{
public:
	SpriteStore();
	void updateSpritePosition(const std::string& direction, const float& x_pos, const float& y_pos);
	virtual void updateSpriteTexture() = 0;
    sf::Sprite getSprite() const;
	virtual void loadTextures() = 0;

private:
	bool toTheLeft;
	bool toTheRight;
	sf::Sprite entitySprite;
};
#endif // !SPRITESTORE_H

