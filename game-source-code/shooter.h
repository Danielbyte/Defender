#ifndef SHOOTER_H
#define SHOOTER_H
#include <string>
#include <tuple>
#include <vector>
#include <memory>
#include "projectile.h"

class Shooter
{
public:
	Shooter();
	//Shooter(const float& x, const float& y, const std::string _direction, const float& horizontalOffset,
		//const float& verticalOffset);
	virtual void updateProjectile(const float& dt);
	void createProjectile(std::shared_ptr<Projectile>& projectile);
	
protected:
	std::vector<std::shared_ptr<Projectile>>projectiles;
};
#endif // !PROJECTILE_H

