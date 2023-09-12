#include "game.h"

Game::Game():
	windowWidth{800ul},
	windowHeight{600ul},
	isPlaying{false},
	window(sf::VideoMode(windowWidth, windowHeight), "Defender"),
	upPressed{false},
	downPressed{false},
	leftPressed{false},
	rightPressed{false},
	spacePressed{false}
{
	

	// Load the text font
	font.loadFromFile("resources/sansation.ttf");

	// Initialize the pause message
	splashScreenText.setFont(font);
	splashScreenText.setCharacterSize(20);
	splashScreenText.setPosition(10.f, 180.f);
	splashScreenText.setFillColor(sf::Color::White);
	splashScreenText.setString("Welcome to Defender!\nPress Enter to start the game");


	background_t.loadFromFile("resources/background.png");
	background_s.setTexture(background_t);
	background_s.setOrigin(windowWidth/2.0f, windowHeight/2.0f);
	background_s.setPosition(windowWidth/2.0f,windowHeight/2.0f);

	game_world->placeHumanoids(humanoid_objects, humanoid_sprites);
}

void Game::run()
{
	sf::Clock clock;
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	while (window.isOpen())
	{
			float deltaTime = clock.restart().asSeconds();
			// Handle player input
			handleInput();

			//Update game loop
			updateGame(deltaTime);

			//Draw game entities
			display();
	}
}
