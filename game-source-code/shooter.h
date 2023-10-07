#ifndef SHOOTER_H
#define SHOOTER_H
#include <string>
#include <tuple>
#include <vector>
#include <memory>
#include "projectile.h"
#include "missileSprite.h"

class Shooter
{
public:
	Shooter();
	static void updateProjectile(float dt,const ProjectileType type, std::vector<std::shared_ptr<MissileSprite>>& missile_sprites);
	void updateProjectile(const float dt, std::vector<std::shared_ptr<Projectile>>& projectile);
	static void deleteProjectile(unsigned long long int Id);
	static void createProjectile(std::shared_ptr<Projectile>& projectile);
    std::vector<std::shared_ptr<Projectile>> getProjectiles();
	
protected:
	static std::vector<std::shared_ptr<Projectile>>projectiles;
};
#endif // !PROJECTILE_H

