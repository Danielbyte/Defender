#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <string>
#include <tuple>

class Projectile
{
public:
	Projectile();
	Projectile(const float& x, const float& y, const std::string _direction);
	virtual void updateProjectile(const float& dt);
	std::tuple<float, float> getProjectilePosition() const;

private:
	float xPosition;
	float yPosition;
	std::string direction;
	float projectileSpeed;
};
#endif // !PROJECTILE_H

