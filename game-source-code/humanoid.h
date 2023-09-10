#ifndef HUMANOID_H
#define HUMANOID_H

#include <string>

enum class HumanoidState{Walking,Abducted,Falling};

class Humanoid
{
public:
	Humanoid();
	Humanoid(const float initXpos,const float initYpos, std::string _direction);
	HumanoidState getHumanoidState() const;
	void setHumanoidState(const HumanoidState _state);
	std::string getHumanoidDirection() const;

private:
	HumanoidState state;
	std::string direction;
	float xPosition;
	float yPosition;

};
#endif // !HUMANOID_H

