#ifndef HUMANOID_H
#define HUMANOID_H

enum class HumanoidState{Walking,Abducted,Falling};

class Humanoid
{
public:
	Humanoid();
	HumanoidState getHumanoidState() const;
	void setHumanoidState(const HumanoidState _state);

private:
	HumanoidState state;

};
#endif // !HUMANOID_H

