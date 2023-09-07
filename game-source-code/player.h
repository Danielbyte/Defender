#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "playerSprite.h"
#include "projectile.h"
#include "LaserSprite.h"
#include <memory>
#include <tuple>
#include <vector>
#include <random>

class Player
{
public:
	Player();
	void updatePlayer(const bool& left, const bool& right,const bool& up, const bool& down, bool& space,
		std::shared_ptr<PlayerSprite>& player_sprite, 
		std::vector<std::shared_ptr<Projectile>>& laser_projectile,
		std::vector<std::shared_ptr<LaserSprite>>& laser_sprite,const float& dt);

	std::tuple<float,float> getPlayerPosition() const;

private:
	float x_playerPosition;
	float y_playerPosition;
	float movementConstant;
	std::string direction;

};
#endif // !PLAYER_H

