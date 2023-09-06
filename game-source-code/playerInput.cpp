#include "game.h"

void Game::handleInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			isPlaying = false;
			window.close();
			break;
		}
		
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				isPlaying = false;
				window.close();
				break;

			case sf::Keyboard::Enter:
				isPlaying = true;
				break;

			default:
				break;
			}
		}
		else
		{

		}
	}
}
