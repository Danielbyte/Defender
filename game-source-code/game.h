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
#include "minimap.h"
#include "bombers.h"
#include "bomberSprite.h"
#include "scoreManager.h"

class Game
{
public:
	Game();
	void run();
	void handleInput(); //Defined in playerInput.cpp
	void updateGame(const float dt); //Defined in update.cpp
	void updateLanders(const float dt);
	void updateHumanoids(const float dt);
	void updateBombers(const float dt);
	void updateCollisions();
	void updateProjectiles(const float dt);
	void display(const float dt); //Defined in displayManager.cpp
	void updateGameState();
private:
	void updateCamera();
	void updateBackgroundView();
	void updateScore();

	//Window
	unsigned int windowWidth = 800ul;
	unsigned int windowHeight = 600ul;
	bool isPlaying;
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>
		(sf::VideoMode(windowWidth, windowHeight), "Defender");

	sf::Text splashScreenText;
	sf::Text endOfGame;
	sf::Text winText;
	sf::Font font;

	sf::Texture background_t;
	sf::Sprite background_s;
	sf::Vector2f background1Position;

	//View to set up the camera for scrolling
	sf::View gameView;
	sf::Vector2f viewCenter;
	sf::Vector2f gameViewSize;

	//Mini-map views
	sf::View miniMapView;
	sf::Vector2f miniMapViewSize;

	//Minimap
	sf::Vector2f miniMapSectionPosition;
	sf::Texture miniMapSection_t;
	sf::Sprite miniMapSection_s;

	//Player movement variables
	bool upPressed;
	bool downPressed;
	bool leftPressed;
	bool rightPressed;
	bool spacePressed;
	bool isMoving;

	//GAME ENTITIES
	std::shared_ptr<Minimap> minimap = std::make_shared<Minimap>();
	
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
	std::vector<std::shared_ptr<Projectile>>lasers;

	//Lander Entities
	std::vector<std::shared_ptr<Lander>> lander_objects;
	std::vector<std::shared_ptr<LanderSprite>> lander_object_sprites;
	std::vector<std::shared_ptr<MissileSprite>> lander_missile_sprites;

	//Bomber entity
	std::vector<std::shared_ptr<Bombers>> bombers;
	std::vector<std::shared_ptr<BomberSprite>> bomber_sprites;
	std::vector<std::shared_ptr<Mine>> mines;
	std::vector<std::shared_ptr<MineSprite>> mine_sprites;

	//Collision object
	CollisionsManager update_collisions;

	//Shooter object to update projectiles
	std::shared_ptr<Shooter>shooter_object = std::make_shared<Shooter>();

	//Score Management
	std::shared_ptr<ScoreManager>manage_score = std::make_shared<ScoreManager>();
	sf::Text highScore;
	sf::Text currentScore;
	sf::Vector2f highScorePosition;
	sf::Vector2f currentScorePosition;

	bool gameOver;
	bool playerWon;
	int landersDestroyed;
	int number0fHumanoids;
	float gameWorldWidth; //Width of game world, for a universe that wraps around
};
#endif

