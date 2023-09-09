#ifndef ENEMY_H
#define ENEMY_H

#include "stopWatch.h"
#include <vector>
#include <memory>

class Projectile
{
public:
	Projectile();

protected:
	std::shared_ptr<StopWatch>projectile_watch;

private:

};
#endif // !ENEMY_H

