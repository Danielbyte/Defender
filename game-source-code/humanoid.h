#ifndef HUMANOID_H
#define HUMANOID_H

#include <string>
#include <tuple>
#include "humanoidSprite.h"
#include <memory>
#include <iostream>
#include <random>
#include "player.h"


enum class HumanoidState{Walking,Abducted,Falling,Dead,Rescued,Turning};

class Humanoid
{
public:
	Humanoid();
	HumanoidState getHumanoidState() const;
	void setHumanoidState(const HumanoidState _state);
	std::string getHumanoidDirection() const;
	std::tuple<float, float> getPosition() const;
	void updateHumanoid(const float dt, std::shared_ptr<HumanoidSprite>& humanoid_sprite, std::shared_ptr<Player>& p);
	void updateHumanoid(std::shared_ptr<Player>& player, std::shared_ptr<HumanoidSprite>& humanoid_sprite);
	void placeHumanoid();
	void setToAbducted();
	void setAbductingLanderId(const unsigned int);
	unsigned int getAbductingLanderId() const;
	void setDistance(const float distance);

private:
	void updateHumanoidSprite(std::shared_ptr<HumanoidSprite>& humanoid_sprite);
	void generateXposition();
	void generateDirection();
	void canChangeDirection(); //Decision if humanoid should change direction
	HumanoidState state;
	std::string direction;
	std::string previous_direction;
	std::string new_direction;
	float xPosition;
	float yPosition;
	float speed;
	std::shared_ptr<StopWatch>humanoid_watch = std::make_shared<StopWatch>();
	unsigned int abductingLanderId;
	float distance;
	bool changingDirection;
};
#endif // !HUMANOID_H

