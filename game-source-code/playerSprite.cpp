#include "playerSprite.h"

PlayerSprite::PlayerSprite():
	animation_period{0.105f}
{
	sf::Vector2f dimensions;
	sf::Vector2f miniDimensions;
	sf::Vector2f animationDimensions;
	animationDimensions.x = 400.0f;
	animationDimensions.y = 400.0f;
	dimensions.x = 50.0f;
	dimensions.y = 20.0f;
	miniDimensions.x = 27.0f;
	miniDimensions.y = 10.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions, miniDimensions, animationDimensions);
}

void PlayerSprite::loadTextures()
{
	player_tR.loadFromFile("resources/spaceship-right.png");
	player_tL.loadFromFile("resources/spaceship-left.png");
	miniPlayer_t.loadFromFile("resources/mini-player.png");
	crushing1_t.loadFromFile("resources/crushing-player1.png");
	crushing2_t.loadFromFile("resources/crushing-player2.png");
	crushing3_t.loadFromFile("resources/crushing-player3.png");
	crushing4_t.loadFromFile("resources/crushing-player4.png");
	crushing5_t.loadFromFile("resources/crushing-player5.png");
	crushing6_t.loadFromFile("resources/crushing-player6.png");
}

void PlayerSprite::setTexture(std::string playerState, bool& gameOver, StopWatch& animation_watch)
{
	auto left = getIfLeft();
	auto right = getIfRight();

	if (playerState == "dead")
	{
		if (left)
		{
			setCrushingTexture(animation_watch);
			if ((animation_watch.time_elapsed() > 6 * animation_period))
				gameOver = true;

			return;
		}

		setCrushingTexture(animation_watch);
		if ((animation_watch.time_elapsed() > 6 * animation_period))
			gameOver = true;

		return;
	}

	if (right)
	{
		updateSpriteTexture(player_tR, miniPlayer_t);
	}

	if (left)
	{
		updateSpriteTexture(player_tL, miniPlayer_t);
	}
}

void PlayerSprite::setCrushingTexture(StopWatch& animation_watch)
{
	auto _time = animation_watch.time_elapsed();
	if (_time >= 0.0f && _time <= animation_period)
		updateAnimationSpriteTexture(crushing1_t, miniPlayer_t);

	if (_time > animation_period && _time <= 2 * animation_period)
		updateAnimationSpriteTexture(crushing2_t, miniPlayer_t);

	if (_time > 2 * animation_period && _time <= 3 * animation_period)
		updateAnimationSpriteTexture(crushing3_t, miniPlayer_t);

	if (_time > 3 * animation_period && _time <= 4 * animation_period)
		updateAnimationSpriteTexture(crushing4_t, miniPlayer_t);

	if (_time > 4 * animation_period && _time <= 5 * animation_period)
		updateAnimationSpriteTexture(crushing5_t, miniPlayer_t);

	if (_time > 5 * animation_period && _time <= 6 * animation_period)
		updateAnimationSpriteTexture(crushing6_t, miniPlayer_t);
}