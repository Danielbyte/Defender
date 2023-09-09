#ifndef ENEMY_H
#define ENEMY_H

#include "stopWatch.h"
#include <vector>
#include <memory>
#include <string>

class Projectile
{
public:
	Projectile();
	Projectile(const float& x, const float& y, const std::string _direction, const float& horizontalOffset,
		const float& verticalOffset, const float _targetXpos, const float _targetYpos);

	std::tuple<float, float> getProjectilePosition() const;

	std::string getProjectileDirection() const;
	void updatePosition(const float x, const float y);
	float getProjectileSpeed() const;

	std::tuple<float,float> getInitialProjectilePosition() const;
	std::tuple<float, float> getTargetPosition() const;

protected:
	std::shared_ptr<StopWatch>projectile_watch;


private:
	float projectileSpeed;
	std::string direction;
	float xPosition;
	float yPosition;

	//Projectile should store reference of player position (at firing moment)
	float targetXpos;
	float targetYpos;
	//Initial position of missile
	float initialXpos;
	float initialYpos;

};
#endif // !ENEMY_H

