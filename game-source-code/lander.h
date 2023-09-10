#ifndef LANDER_H
#define LANDER_H

#include "shooter.h"
#include "landerSprite.h"
#include "player.h"
#include "missileSprite.h"

enum class Direction { North, South, East, West, NorthEast, SouthEast, SouthWest, NorthWest, Unknown };

class Lander : public Shooter
{
public:
	Lander();
	std::tuple<float, float> getPosition() const;
	void generateInitialPosition();

	void updateLander(std::shared_ptr<LanderSprite>& lander_sprite,const float& dt,std::shared_ptr<Player>& player,
		std::vector<std::shared_ptr<MissileSprite>>& missile_sprites);

	//model Lander movements
	void moveEast(const float& dt);
	void moveWest(const float& dt);
	void moveNorth(const float& dt);
	void moveSouth(const float& dt);
	void moveNorthEast(const float& dt);
	void moveSouthEast(const float& dt);
	void moveSouthWest(const float& dt);
	void moveNorthWest(const float& dt);
	void pickDirection();
	void restrictLander(const float& dt); //Restrict lander to hover around humanoid zone


	void updateMissileSprites(std::vector<std::shared_ptr<MissileSprite>>& missile_sprites);
	
private:
	float xPosition;
	float yPosition;
	bool rightSide;
	bool leftSide;
	float landerSpeed;
	bool reachedHumanoidZone;
	std::shared_ptr<StopWatch>lander_watch = std::make_shared<StopWatch>();
	std::shared_ptr<StopWatch>movement_watch = std::make_shared<StopWatch>();
	Direction direction;
	//Reference to player position
	float playerXposref;
	float playerYposref;
	void createMissiles(std::vector<std::shared_ptr<MissileSprite>>& missile_sprites);
	float missileSpeed;
};
#endif // !LANDER_H

