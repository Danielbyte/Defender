#ifndef HUMANOID_H
#define HUMANOID_H

#include <string>
#include <tuple>
#include "humanoidSprite.h"
#include <memory>


enum class HumanoidState{Walking,Abducted,Falling, Dead};

class Humanoid
{
public:
	Humanoid();
	Humanoid(const float initXpos,const float initYpos, std::string _direction);
	HumanoidState getHumanoidState() const;
	void setHumanoidState(const HumanoidState _state);
	std::string getHumanoidDirection() const;
	std::tuple<float, float> getPosition() const;
	void updateHumanoid(const float dt, std::shared_ptr<HumanoidSprite>& humanoid_sprite);

private:
	void updateHumanoidSprite(std::shared_ptr<HumanoidSprite>& humanoid_sprite);
	HumanoidState state;
	std::string direction;
	float xPosition;
	float yPosition;
	float speed;
};
#endif // !HUMANOID_H

