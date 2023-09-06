#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "playerSprite.h"
#include <memory>
#include <tuple>

class Player
{
public:
	Player();
	void updatePlayer(const bool& left, const bool& right,const bool& up, const bool& down,
		std::shared_ptr<PlayerSprite>& sprite_store, const float& dt);

	std::tuple<float,float> getPlayerPosition() const;

private:
	float x_playerPosition;
	float y_playerPosition;
	float movementConstant;

};
#endif // !PLAYER_H

