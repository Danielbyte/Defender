#ifndef ENEMY_H
#define ENEMY_H

#include "stopWatch.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

enum class ProjectileType { Laser, LanderMissile };

class Projectile
{
public:
	Projectile();
	Projectile(const float x, const float y, const std::string _direction, const float horizontalOffset,
		const float verticalOffset, const float _targetXpos, const float _targetYpos,
		unsigned long long int projectileId, ProjectileType _typeOfShooter, const float _speed);

	std::tuple<float, float> getProjectilePosition() const;

	std::string getProjectileDirection() const;

	void updateFrameCounter();
	float getFrameCounter() const;
	void updateTrajectory(const float x);
	void calculateTrajectoryConstants();
	void updatePosition(const float x, const float y);
	unsigned long long int getProjectileId() const;
	ProjectileType getType() const;
	float getSpeed() const;
	void setNewId(unsigned long long int newId);
	bool getDelete() const;

private:
	std::string direction;
	float xPosition;
	float yPosition;

	//Projectile should store reference of player position (at firing moment)
	float targetXpos;
	float targetYpos;
	//Initial position of missile
	float initialXpos;
	float initialYpos;

	int frame_counter; //monitors the animations of projectile animation

	float slope;
	float yIntercept;

	unsigned long long int projectileId;

	ProjectileType typeOfShooter;
	float speed;
	bool Delete;
	std::shared_ptr<StopWatch>lifeTime = std::make_shared<StopWatch>();
	std::shared_ptr<StopWatch>color_watch = std::make_shared<StopWatch>();
};
#endif // !ENEMY_H

