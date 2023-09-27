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
	spacePressed{false},
	isMoving{false},
	gameOver{false},
	playerWon{false}
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
	endOfGame.setFillColor(sf::Color::White);
	endOfGame.setString("GAME OVER!");

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

	miniMap_t.loadFromFile("resources/minimap.png");
	miniMap_s.setTexture(miniMap_t);
	miniMapPosition.x = windowWidth / 2.0f;
	miniMapPosition.y = 51.0f;
	miniMap_s.setOrigin(400.0f, 50.0f);
	miniMap_s.setPosition(miniMapPosition);

	miniTerrain1_t.loadFromFile("resources/terrain-1-mini.png");
	miniTerrain1_s.setTexture(miniTerrain1_t);
	miniTerrain1_s.setOrigin(800.0f, 30 / 2.0f);
	t1Pos.x = 450.0f;
	t1Pos.y = 85.0f;
	miniTerrain1_s.setPosition(t1Pos);

	miniTerrain2_t.loadFromFile("resources/terrain-2-mini.png");
	miniTerrain2_s.setTexture(miniTerrain2_t);
	miniTerrain2_s.setOrigin(600.0f, 18 / 2.0f);
	miniTerrain2_s.setPosition(315.5f, 91.5f);

	miniMainSection_t.loadFromFile("resources/miniMainSection.png");
	miniMainSection_s.setTexture(miniMainSection_t);
	miniMainSection_s.setOrigin(150 / 2.0f, 99 / 2.0f);
	miniMainSection_s.setPosition(388.0f, 51.0f);	
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
