#include "game.h"

Game::Game():
	isPlaying{false},
	upPressed{false},
	downPressed{false},
	leftPressed{false},
	rightPressed{false},
	spacePressed{false},
	isMoving{false},
	gameOver{false},
	playerWon{false},
	landersDestroyed{0}
{
	viewCenter.x = 400.0f;
	viewCenter.y = windowHeight / 2.0f;
	gameViewSize.x = 800.0f;
	gameViewSize.y = 600.0f;
	gameView.setCenter(viewCenter);
	gameView.setSize(gameViewSize);

	miniMapViewSize.x = 800.0f;
	miniMapViewSize.y = 600.0f;
	miniMapView.setSize(miniMapViewSize);
	miniMapView.setCenter(viewCenter);
	miniMapView.setViewport(sf::FloatRect(0.3125f, 0.0f, 0.375f, 1.0f));

	// Load the text font
	font.loadFromFile("resources/sansation.ttf");

	// Initialize the pause message
	splashScreenText.setFont(font);
	splashScreenText.setCharacterSize(20);
	splashScreenText.setPosition(10.f, 180.f);
	splashScreenText.setFillColor(sf::Color::White);
	splashScreenText.setString("Welcome to Defender!\nPress Enter to start the game");

	endOfGame.setFont(font);
	endOfGame.setCharacterSize(40);
	endOfGame.setPosition(20.f, 90.f);
	endOfGame.setFillColor(sf::Color::Red);
	endOfGame.setString("GAME OVER!\nPress Esc to quit");

	winText.setFont(font);
	winText.setCharacterSize(40);
	winText.setPosition(20.f, 90.f);
	winText.setFillColor(sf::Color::Green);
	winText.setString("YOU WON!\nPress Esc to quit");

	background_t.loadFromFile("resources/background.png");
	background_s.setTexture(background_t);
	background_s.setOrigin(3200/2.0f, windowHeight/2.0f);
	background1Position.x = 1800.0f;
	background1Position.y = windowHeight / 2.0f;
	background_s.setPosition(background1Position);
	landscape1->updateTerrain(landscape1_sprite, background1Position.x);

	background_t2.loadFromFile("resources/background2.png");
	background_s2.setTexture(background_t2);
	background_s2.setOrigin(3200 / 2.0f, windowHeight / 2.0f);
	background2Position.x = -1400.0f;
	background2Position.y = windowHeight / 2.0f;
	background_s2.setPosition(background2Position);
	landscape2->updateTerrain(landscape2_sprite, background2Position.x);

	game_world->placeHumanoids(humanoid_objects, humanoid_sprites);

	miniMapSection_t.loadFromFile("resources/minimap.png");
	miniMapSection_s.setTexture(miniMapSection_t);
	miniMapSectionPosition.x = windowWidth / 2.0f;
	miniMapSectionPosition.y = 51.0f;
	miniMapSection_s.setOrigin(400.0f, 50.0f);
	miniMapSection_s.setPosition(miniMapSectionPosition);

	miniMainSection_t.loadFromFile("resources/miniMainSection.png");
	miniMainSection_s.setTexture(miniMainSection_t);
	miniMainSection_s.setOrigin(400 / 2.0f, 100 / 2.0f);
	gameSectionPosition.x = 0.0f;
	gameSectionPosition.y = 51.0f;
	miniMainSection_s.setPosition(0.0f, 51);	
}

void Game::run()
{
	sf::Clock clock;
	window->setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	while (window->isOpen())
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
