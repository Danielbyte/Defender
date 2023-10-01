#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include "spriteStore.h"

class PlayerSprite : public SpriteStore
{
public:
	PlayerSprite();
	void virtual loadTextures();
	void setTexture(std::string playerState, bool& gameOver, StopWatch& animation_watch);

private:
	sf::Texture player_tR;
	sf::Texture player_tL;
	sf::Texture player_death_tR;
	sf::Texture player_death_TL;
	sf::Texture miniPlayer_t;
};

#endif // !PLAYERSPRITE_H

