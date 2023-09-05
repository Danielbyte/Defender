#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Game
{
public:
	Game();
	void run();
private:
	unsigned int gameWidth;
	unsigned int gameHeight;
	sf::RenderWindow window;
};
#endif

