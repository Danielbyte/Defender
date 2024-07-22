#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "playerSprite.h"
#include "shooter.h"
#include "LaserSprite.h"
#include <memory>
#include <tuple>
#include <random>

enum class PlayerState{Alive, Dead};

class Player : Shooter
{
public:
	Player();
	void updatePlayer(const bool& left, const bool& right,const bool& up, const bool& down, bool& space,
		std::shared_ptr<PlayerSprite>& player_sprite, std::vector<std::shared_ptr<LaserSprite>>& laser_sprite, 
		std::vector<std::shared_ptr<Projectile>>& lasers, const float dt, bool& gameOver);

	void scalePosition(float horizontalScalingRatio, float verticalScalingRatio);

	std::tuple<float,float> getPlayerPosition() const;
	void createLasers(std::vector<std::shared_ptr<LaserSprite>>& laser_sprite, std::vector<std::shared_ptr<Projectile>>& lasers);
	void updateLasers(std::vector<std::shared_ptr<LaserSprite>>& laser_sprites, std::vector<std::shared_ptr<Projectile>>& lasers,const float dt);
	std::string getDirection() const;
	void restartAnimationWatch();
	void setPlayerState(PlayerState _state);
	PlayerState getPlayerState() const;
	void updatePlayerScore(const int points);
	int getScore() const;

private:
	float x_playerPosition;
	float y_playerPosition;
	float playerSpeed;
	std::string direction;
	float laserSpeed;
	PlayerState state;
	int playerScore;
	StopWatch animation_watch;
	float downBoundary;
	float upBoundary;

};
#endif // !PLAYER_H

