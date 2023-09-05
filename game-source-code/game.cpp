#include "game.h"

Game::Game():
	gameWidth{800ul},
	gameHeight{600ul},
	window(sf::VideoMode(gameWidth, gameHeight), "Defender")

{
	window.setVerticalSyncEnabled(true);

	// Load the text font
	if (!font.loadFromFile("resources/sansation.ttf"))

	// Initialize the pause message
	splashScreenText.setFont(font);
	splashScreenText.setCharacterSize(40);
	splashScreenText.setPosition(170.f, 150.f);
	splashScreenText.setFillColor(sf::Color::White);
	splashScreenText.setString("Welcome to SFML PONG!\nPress space to start the game");
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
					window.close();
					break;
				}

				// Space key pressed: play
				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
				{

				}
			}
			if (isPlaying)
			{

		    }

		    else
		    {
			   window.draw(splashScreenText);
		    }
			// Display things on screen
			window.display();
			window.clear();
	}
}
