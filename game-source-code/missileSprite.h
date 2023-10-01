#ifndef MISSILESPRITE_H
#define MISSILESPRITE_H

#include "spriteStore.h"

class MissileSprite : public SpriteStore
{
public:
	MissileSprite();
	void virtual loadTextures();
	void setTexture(const int _time);

private:
	sf::Texture missile1_t;
	sf::Texture missile2_t;
	sf::Texture NA;
	float sprite_period; //time witch a sprite should display

};
#endif // !MISSILESPRITE_H

