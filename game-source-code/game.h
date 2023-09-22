#ifndef GAME_H
#define GAME_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "player.h"
#include "lander.h"
#include "gameWorld.h"
#include "collisionsManager.h"
#include "humanoidSprite.h"
#include "landscape.h"
#include "landscapeSprite.h"

class Game
{
public:
	Game();
	void run();
	void handleInput(); //Defined in playerInput.cpp
	void updateGame(const float dt); //Defined in update.cpp
	void updateLanders(const float dt);
	void updateHumanoids(const float dt);
	void updateCollisions();
	void updateProjectiles(const float dt);
	void display(const float dt); //Defined in displayManager.cpp
private:
	void updateCamera(const float dt);
	void updateBackgroundView();

	//Window
	unsigned int windowWidth;
	unsigned int windowHeight;
	bool isPlaying;
	sf::RenderWindow window;
	sf::Text splashScreenText;
	sf::Font font;

	sf::Texture background_t;
	sf::Sprite background_s;
	sf::Texture background_t2;
	sf::Sprite background_s2;
	sf::Vector2f background1Position;
	sf::Vector2f background2Position;

	//View to set up the camera for scrolling
	sf::View gameView;
	sf::Vector2f viewCenter;
	sf::Vector2f viewSize;

	//Minimap
	sf::Texture viewDivider_t;
	sf::Sprite viewDivider_s;
	sf::Texture miniMapBorders_t;
	sf::Sprite miniManpBorders_s;

	//Player movement variables
	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	bool spacePressed;

	//GAME ENTITIES
	
	//Humanoid objects
	std::vector<std::shared_ptr<Humanoid>> humanoid_objects;
	std::vector<std::shared_ptr<HumanoidSprite>> humanoid_sprites;

	// game world
	std::shared_ptr<GameWorld> game_world = std::make_shared<GameWorld>();
	std::shared_ptr<Landscape> landscape1 = std::make_shared<Landscape>();
	std::shared_ptr<LandscapeSprite> landscape1_sprite = std::make_shared<LandscapeSprite>(1);
	std::shared_ptr<Landscape> landscape2 = std::make_shared<Landscape>();
	std::shared_ptr<LandscapeSprite> landscape2_sprite = std::make_shared<LandscapeSprite>(2);

	//Player Entity
	std::shared_ptr<Player> player_obj = std::make_shared<Player>();
	std::shared_ptr<PlayerSprite>player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprite;

	//Lander Entities
	std::vector<std::shared_ptr<Lander>> lander_objects;
	std::vector<std::shared_ptr<LanderSprite>> lander_object_sprites;
	std::vector<std::shared_ptr<MissileSprite>> lander_missile_sprites;

	//Collision object
	CollisionsManager update_collisions;

	//Shooter object to update projectiles
	std::shared_ptr<Shooter>shooter_object = std::make_shared<Shooter>();
};
#endif

