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
	sf::Texture miniPlayer_t;
	sf::Texture crushing1_t;
	sf::Texture crushing2_t;
	sf::Texture crushing3_t;
	sf::Texture crushing4_t;
	sf::Texture crushing5_t;
	float animation_period;

	void setCrushingTexture(StopWatch& animation_watch);
};

#endif // !PLAYERSPRITE_H

