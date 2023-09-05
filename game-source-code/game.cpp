#include "game.h"

Game::Game():
	gameWidth{800ul},
	gameHeight{600ul},
	window(sf::VideoMode(gameWidth, gameHeight), "Defender", sf::Style::Titlebar | sf::Style::Close)

{
	window.setVerticalSyncEnabled(true);
}

void Game::run()
{
	sf::Clock clock;
	bool isPlaying = false;
	while (window.isOpen())
	{
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

			if (isPlaying)
			{
				float deltaTime = clock.restart().asSeconds();
			}

			// Display things on screen
			window.display();
		}
	}
}
