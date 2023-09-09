#include "collisions.h"

Collisions::Collisions() {}

bool Collisions::checkCollision(float obj1Xposition, float obj1Yposition, float obj1Width, float obj1Length,
	float obj2Xposition, float obj2Yposition, float obj2Width, float obj2Length)
{
	float obj1Left = obj1Xposition - (obj1Length / 2.0f);
	float obj1Right = obj1Xposition + (obj1Length / 2.0f);
	float obj1Top = obj1Yposition - (obj1Width / 2.0f);
	float obj1Bottom = obj1Yposition + (obj1Width / 2.0f);

	float obj2Left = obj2Xposition - (obj2Length / 2.0f);
	float obj2Right = obj2Xposition + (obj2Length / 2.0f);
	float obj2Top = obj2Yposition - (obj2Width / 2.0f);
	float obj2Bottom = obj2Yposition + (obj2Width / 2.0f);
}
