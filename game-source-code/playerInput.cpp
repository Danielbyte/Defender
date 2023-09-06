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

			case sf::Keyboard::Up:
				upPressed = true;
				break;

			case sf::Keyboard::Down:
				downPressed = true;
				break;

			case sf::Keyboard::Left:
				leftPressed = true;
				break;

			case sf::Keyboard::Right:
				rightPressed = true;
				break;

			case sf::Keyboard::Space:
				//Load player ship bullets
				break;

			default:
				break;
			}
		}

		else
		{
			upPressed = false;
			downPressed = false;
			leftPressed = false;
			rightPressed = false;
		}
	}
}
