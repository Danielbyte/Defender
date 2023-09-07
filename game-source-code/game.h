#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include "player.h"

class Game
{
public:
	Game();
	void run();
	void handleInput(); //Defined in playerInput.cpp
	void updateGame(const float dt); //Defined in update.cpp
	void display(); //Defined in displayManager.cpp
private:
	unsigned int windowWidth;
	unsigned int windowHeight;
	bool isPlaying;
	sf::RenderWindow window;
	sf::Text splashScreenText;
	sf::Font font;

	sf::Texture player_t;
	sf::Sprite player_s;

	sf::Texture background_t;
	sf::Sprite background_s;

	//Player movement variables
	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;

	//game objects
	std::shared_ptr<Player> player_obj = std::make_shared<Player>();
	std::shared_ptr<PlayerSprite>player_sprite = std::make_shared<PlayerSprite>();
};
#endif
