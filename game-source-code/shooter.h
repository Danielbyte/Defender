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
	virtual void updateProjectile(float dt);
	void createProjectile(std::shared_ptr<Projectile>& projectile);
	std::vector<std::shared_ptr<Projectile>> getProjectiles();
	
protected:
	std::vector<std::shared_ptr<Projectile>>projectiles;
};
#endif // !PROJECTILE_H

