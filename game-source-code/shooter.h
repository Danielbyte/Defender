#ifndef SHOOTER_H
#define SHOOTER_H
#include <string>
#include <tuple>
#include <vector>
#include <memory>

class Shooter
{
public:
	Shooter();
	Shooter(const float& x, const float& y, const std::string _direction, const float& horizontalOffset);
	virtual void updateProjectile(const float& dt);
	std::tuple<float, float> getProjectilePosition() const;
	void createProjectile(std::shared_ptr<Shooter>& projectile);

protected:
	std::vector<std::shared_ptr<Shooter>>projectiles;

private:
	float xPosition;
	float yPosition;
	std::string direction;
	float projectileSpeed;
};
#endif // !PROJECTILE_H

