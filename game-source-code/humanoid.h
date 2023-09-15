#ifndef HUMANOID_H
#define HUMANOID_H

#include <string>
#include <tuple>
#include "humanoidSprite.h"
#include <memory>
#include <iostream>
#include <random>


enum class HumanoidState{Walking,Abducted,Falling, Dead};

class Humanoid
{
public:
	Humanoid();
	HumanoidState getHumanoidState() const;
	void setHumanoidState(const HumanoidState _state);
	std::string getHumanoidDirection() const;
	std::tuple<float, float> getPosition() const;
	void updateHumanoid(const float dt, std::shared_ptr<HumanoidSprite>& humanoid_sprite);
	void placeHumanoid();
	void setToAbducted();
	void setAbductingLanderId(const unsigned int);
	unsigned int getAbductingLanderId() const;

private:
	void updateHumanoidSprite(std::shared_ptr<HumanoidSprite>& humanoid_sprite);
	void generateXposition();
	void generateDirection();
	HumanoidState state;
	std::string direction;
	float xPosition;
	float yPosition;
	float speed;
	std::shared_ptr<StopWatch>humanoid_watch = std::make_shared<StopWatch>();
	unsigned int abductingLanderId;
};
#endif // !HUMANOID_H

