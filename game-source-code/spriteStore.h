#ifndef SPRITESTORE_H
#define SPRITESTORE_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class SpriteStore
{
public:
	SpriteStore();
	void updatePlayerShipSprite(const bool& shipDirection);
	sf::Sprite getPlayerShipSprite() const;
	void loadPlayerShipSprites();

private:
	sf::Texture playerShip_lT; // player ship facing left(texture)
	sf::Sprite playerShip_lS; // player ship facing left(sprite)
	sf::Texture playerShip_rT; // player ship facing right(texture)
	sf::Sprite playerShip_rS; // player ship facing right(sprite)
};
#endif // !SPRITESTORE_H

