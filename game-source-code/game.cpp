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
	viewCenter.x = windowWidth / 2.0f;
	viewCenter.y = windowHeight / 2.0f;
	viewSize = 2.0f * viewCenter;
	gameView.setCenter(viewCenter);
	gameView.setSize(viewSize);

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
	background1Position.x = windowWidth / 2.0f;
	background1Position.y = windowHeight / 2.0f;
	background_s.setPosition(background1Position);
	landscape1->updateTerrain(landscape1_sprite, background1Position.x);

	background_t2.loadFromFile("resources/background2.png");
	background_s2.setTexture(background_t2);
	background_s2.setOrigin(windowWidth / 2.0f, windowHeight / 2.0f);
	background2Position.x = (windowWidth / 2.0f) - 600.0f;
	background2Position.y = windowHeight / 2.0f;
	background_s2.setPosition(background2Position);
	landscape2->updateTerrain(landscape2_sprite, background2Position.x);

	game_world->placeHumanoids(humanoid_objects, humanoid_sprites);

	viewDivider_t.loadFromFile("resources/minimap-line.png");
	viewDivider_s.setTexture(viewDivider_t);
	sf::Vector2f lowerLineBoundary;
	sf::Vector2f linePosition;
	linePosition.x = windowWidth / 2.0f;
	linePosition.y = 100.0f;
	lowerLineBoundary.x = static_cast<float>(windowWidth);
	lowerLineBoundary.y = 2.0f;
	viewDivider_s.setOrigin(lowerLineBoundary/2.0f);
	viewDivider_s.setPosition(linePosition);

	miniMapBorders_t.loadFromFile("resources/minimap-borders.png");
	miniManpBorders_s.setTexture(miniMapBorders_t);
	sf::Vector2f miniMapBorderDimensions;
	sf::Vector2f miniMapPosition;
	miniMapPosition.y = 50.0f;
	miniMapBorderDimensions.x = 600.0f;
	miniMapBorderDimensions.y = 100.0f;
	miniManpBorders_s.setOrigin(miniMapBorderDimensions / 2.0f);
	miniManpBorders_s.setPosition(miniMapPosition);
	
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
			display(deltaTime);
	}
}
