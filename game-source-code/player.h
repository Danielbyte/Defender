#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "playerSprite.h"
#include "shooter.h"
#include "LaserSprite.h"
#include <memory>
#include <tuple>
#include <random>

class Player : Shooter
{
public:
	Player();
	void updatePlayer(const bool& left, const bool& right,const bool& up, const bool& down, bool& space,
		std::shared_ptr<PlayerSprite>& player_sprite, 
		std::vector<std::shared_ptr<LaserSprite>>& laser_sprite,const float dt);

	std::tuple<float,float> getPlayerPosition() const;
	void createLasers(std::vector<std::shared_ptr<LaserSprite>>& laser_sprite);
	void updateLasers(std::vector<std::shared_ptr<LaserSprite>>& laser_sprite, const float dt);
	std::string getDirection() const;

private:
	float x_playerPosition;
	float y_playerPosition;
	float playerSpeed;
	std::string direction;
	float laserSpeed;

};
#endif // !PLAYER_H

