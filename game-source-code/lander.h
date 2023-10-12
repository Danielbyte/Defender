#ifndef LANDER_H
#define LANDER_H

#include "shooter.h"
#include "landerSprite.h"
#include "player.h"
#include "missileSprite.h"
#include "humanoid.h"
#include <cmath>

enum class Direction { North, South, East, West, NorthEast, SouthEast, SouthWest, NorthWest, Other };

class Lander : public Shooter
{
public:
	Lander();
	Lander(std::shared_ptr<Player>& player);
	std::tuple<float, float> getPosition() const;
	void generateInitialPosition(std::shared_ptr<Player>& player);

	void updateLander(std::shared_ptr<LanderSprite>& lander_sprite,const float dt,std::shared_ptr<Player>& player,
		std::vector<std::shared_ptr<MissileSprite>>& missile_sprites, std::vector<std::shared_ptr<Humanoid>>& humanoids);

	//model Lander movements
	void moveEast(const float& dt);
	void moveWest(const float& dt);
	void moveNorth(const float& dt);
	void moveSouth(const float& dt);
	void moveNorthEast(const float& dt);
	void moveSouthEast(const float& dt);
	void moveSouthWest(const float& dt);
	void moveNorthWest(const float& dt);
	void pickDirection(std::vector<std::shared_ptr<Humanoid>>& humanoids, const float dt);
	void restrictLander(const float& dt); //Restrict lander to hover around humanoid zone


	void updateMissileSprites(std::vector<std::shared_ptr<MissileSprite>>& missile_sprites);
	bool checkForHumanoid(std::vector<std::shared_ptr<Humanoid>>& humanoids);
	void setToascend();
	void abductionProcess(const float dt);
	unsigned int getLocalId();
    //functions for test purposed
	std::tuple<bool, bool> test_getSide();
	bool test_getIfInHumanoidZone() const;
	bool getIfTeleporting() const;
	void test_setTeleportationState(bool teleporting); // for test purposes only

	void tests_setPosition(float x, float y);
	
private:
	void createMissiles(std::vector<std::shared_ptr<MissileSprite>>& missile_sprites);
	void abductionDecision();
	void generateTeleportPosition(std::shared_ptr<Player>& player);
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
	float missileSpeed;
	bool isAbducting; //lander in the process of abducting a lander
	bool ascend;
	bool isTeleporting;
	static unsigned int globalId;
	unsigned int localId; //Id with same scope as lander object
	static void setId();
	void setLocalId();
};
#endif // !LANDER_H

