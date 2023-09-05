#include "game.h"

Game::Game():
	windowWidth{800ul},
	windowHeight{600ul},
	window(sf::VideoMode(windowWidth, windowHeight), "Defender")

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
}

void Game::run()
{
	sf::Clock clock;
	bool isPlaying = false;
	window.setVerticalSyncEnabled(true);
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
			

			if (!isPlaying)
			{
			    window.draw(splashScreenText);
			}
			else
			{
				window.draw(background_s);
			}
			
			window.display();
			window.clear();
	}
}
