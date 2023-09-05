#include "game.h"

Game::Game():
	windowWidth{800ul},
	windowHeight{600ul},
	window(sf::VideoMode(windowWidth, windowHeight), "Defender")

{
	window.setVerticalSyncEnabled(true);

	// Load the text font
	font.loadFromFile("resources/sansation.ttf");

	// Initialize the pause message
	splashScreenText.setFont(font);
	splashScreenText.setCharacterSize(20);
	splashScreenText.setPosition(10.f, 180.f);
	splashScreenText.setFillColor(sf::Color::White);
	splashScreenText.setString("Welcome to Defender!\nPress Enter to start the game");


	background_t.loadFromFile("resources/background.png");
	background_s.setTexture(player_t);
	//background_s.setOrigin(0,0);
	background_s.setPosition(800.0f,600.0f);
}

void Game::run()
{
	sf::Clock clock;
	bool isPlaying = false;
	while (window.isOpen())
	{
			float deltaTime = clock.restart().asSeconds();
			// Handle events
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Window closed or escape key pressed: exit
				if ((event.type == sf::Event::Closed) ||
					((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
					isPlaying = false;
					window.close();
					break;
				}
				
				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
				{
					isPlaying = true;
				}

			}
			window.clear();

			if (!isPlaying)
			{
				
				//window.draw(splashScreenText);
				window.draw(background_s);
			
			}
			else
			{
				splashScreenText.setString("PLAAAAAAAAAAAAAAAAAAAAAAY");
				window.draw(splashScreenText);
			}
			
			window.display();
			
			
	}
}
