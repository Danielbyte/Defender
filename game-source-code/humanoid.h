#ifndef HUMANOID_H
#define HUMANOID_H

#include <string>
#include <tuple>

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
	void updatePosition(const float dt);

private:
	HumanoidState state;
	std::string direction;
	float xPosition;
	float yPosition;
	float speed;

};
#endif // !HUMANOID_H

