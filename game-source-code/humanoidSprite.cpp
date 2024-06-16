#include "humanoidSprite.h"

HumanoidSprite::HumanoidSprite():
	texture_period{0.08f}
{
	sf::Vector2f dimensions;
	dimensions.x = 48.0f;
	dimensions.y = 48.0f;
	sf::Vector2f miniDimensions;

	sf::Vector2f NA;

	InitialiseEntityOrigin(dimensions, miniDimensions, NA);
	loadTextures();
}

void HumanoidSprite::loadTextures()
{
	humanoid1_t.loadFromFile("resources/humanoid1.png");
	humanoid2_t.loadFromFile("resources/humanoid2.png");
	humanoid3_t.loadFromFile("resources/humanoid3.png");
	humanoid4_t.loadFromFile("resources/humanoid4.png");
	humanoid5_t.loadFromFile("resources/humanoid5.png");
	humanoid6_t.loadFromFile("resources/humanoid6.png");
	humanoid7_t.loadFromFile("resources/humanoid7.png");
	humanoid8_t.loadFromFile("resources/humanoid8.png");
	humanoid9_t.loadFromFile("resources/humanoid9.png");
	humanoid10_t.loadFromFile("resources/humanoid10.png");
	humanoid11_t.loadFromFile("resources/humanoid11.png");
	humanoid12_t.loadFromFile("resources/humanoid12.png");
	humanoid13_t.loadFromFile("resources/humanoid13.png");
	humanoid14_t.loadFromFile("resources/humanoid14.png");
	humanoid15_t.loadFromFile("resources/humanoid15.png");
	humanoid16_t.loadFromFile("resources/humanoid16.png");
	humanoid17_t.loadFromFile("resources/humanoid17.png");
	humanoid18_t.loadFromFile("resources/humanoid18.png");
	humanoid19_t.loadFromFile("resources/humanoid19.png");
	humanoid20_t.loadFromFile("resources/humanoid20.png");
	humanoid21_t.loadFromFile("resources/humanoid21.png");
	humanoid22_t.loadFromFile("resources/humanoid22.png");
	humanoid23_t.loadFromFile("resources/humanoid23.png");
	humanoid24_t.loadFromFile("resources/humanoid24.png");
	humanoid25_t.loadFromFile("resources/humanoid25.png");
	humanoid26_t.loadFromFile("resources/humanoid26.png");
	humanoid27_t.loadFromFile("resources/humanoid27.png");
	humanoid28_t.loadFromFile("resources/humanoid28.png");
	humanoid29_t.loadFromFile("resources/humanoid29.png");
	humanoid30_t.loadFromFile("resources/humanoid30.png");
	humanoid31_t.loadFromFile("resources/humanoid31.png");
	humanoid32_t.loadFromFile("resources/humanoid32.png");
	humanoid33_t.loadFromFile("resources/humanoid33.png");
	humanoid34_t.loadFromFile("resources/humanoid34.png");

	//Turning humanoid(s)
	Thumanoid1_t.loadFromFile("resources/Thumanoid1.png");
	Thumanoid2_t.loadFromFile("resources/Thumanoid2.png");
	Thumanoid3_t.loadFromFile("resources/Thumanoid3.png");
	Thumanoid4_t.loadFromFile("resources/Thumanoid4.png");
	Thumanoid5_t.loadFromFile("resources/Thumanoid5.png");
	Thumanoid6_t.loadFromFile("resources/Thumanoid6.png");
	Thumanoid7_t.loadFromFile("resources/Thumanoid7.png");
	Thumanoid8_t.loadFromFile("resources/Thumanoid8.png");
	Thumanoid9_t.loadFromFile("resources/Thumanoid9.png");
	Thumanoid10_t.loadFromFile("resources/Thumanoid10.png");
	Thumanoid11_t.loadFromFile("resources/Thumanoid11.png");
	Thumanoid12_t.loadFromFile("resources/Thumanoid12.png");
	Thumanoid13_t.loadFromFile("resources/Thumanoid13.png");
	Thumanoid14_t.loadFromFile("resources/Thumanoid14.png");
	Thumanoid15_t.loadFromFile("resources/Thumanoid15.png");
	Thumanoid16_t.loadFromFile("resources/Thumanoid16.png");
	Thumanoid17_t.loadFromFile("resources/Thumanoid17.png");
	Thumanoid18_t.loadFromFile("resources/Thumanoid18.png");
	Thumanoid19_t.loadFromFile("resources/Thumanoid19.png");
	Thumanoid20_t.loadFromFile("resources/Thumanoid20.png");;
	Thumanoid21_t.loadFromFile("resources/Thumanoid21.png");;
	Thumanoid22_t.loadFromFile("resources/Thumanoid22.png");;
	Thumanoid23_t.loadFromFile("resources/Thumanoid23.png");;
	Thumanoid24_t.loadFromFile("resources/Thumanoid24.png");;
	Thumanoid25_t.loadFromFile("resources/Thumanoid25.png");;
	Thumanoid26_t.loadFromFile("resources/Thumanoid26.png");;
	Thumanoid27_t.loadFromFile("resources/Thumanoid27.png");;
	Thumanoid28_t.loadFromFile("resources/Thumanoid28.png");;

	fallingHumanoid1_t.loadFromFile("resources/falling-humanoid1.png");
	fallingHumanoid2_t.loadFromFile("resources/falling-humanoid2.png");
	fallingHumanoid3_t.loadFromFile("resources/falling-humanoid3.png");
	miniMap_t.loadFromFile("resources/mini-humanoid.png");
}

void HumanoidSprite::setTexture(std::string direction, const std::string state, float xPos, float yPos,
	std::shared_ptr<StopWatch>humanoid_watch)
{
	auto horizontalOffset = 400.0f;
	auto verticalOffset = 40.0f;
	auto horizontalScalingFactor = 0.5f;
	auto verticalScalingfFactor = 1.0f / 6.0f;
	auto miniMapXpos = (xPos - horizontalOffset) * horizontalScalingFactor;
	auto miniMapYpos = (yPos - verticalOffset) * verticalScalingfFactor;

	if (state == "Walking" || state == "Abducted")
	{
		walkingAndAbuction(direction,humanoid_watch);
		updateSpritePosition(direction, xPos, yPos, miniMapXpos, miniMapYpos);
		return;
	}

	if (state == "Falling")
	{
		falling(direction,humanoid_watch);
		updateSpritePosition(direction, xPos, yPos, miniMapXpos, miniMapYpos);
		return;
	}

	if (state == "Turning")
	{
		turning(direction, humanoid_watch);
		updateSpritePosition(direction, xPos, yPos, miniMapXpos, miniMapYpos);
	}
}

void HumanoidSprite::turning(std::string direction, std::shared_ptr<StopWatch>humanoid_watch)
{
	auto _time = humanoid_watch->time_elapsed();
	if (direction == "left")
	{
		if (_time > 34 * texture_period && _time <= 35 * texture_period)
			updateAnimationSpriteTexture(Thumanoid1_t, miniMap_t);

		if (_time > 35 * texture_period && _time <= 36 * texture_period)
			updateAnimationSpriteTexture(Thumanoid2_t, miniMap_t);

		if (_time > 36 * texture_period && _time <= 37 * texture_period)
			updateAnimationSpriteTexture(Thumanoid3_t, miniMap_t);

		if (_time > 37 * texture_period && _time <= 38 * texture_period)
			updateAnimationSpriteTexture(Thumanoid4_t, miniMap_t);

		if (_time > 38 * texture_period && _time <= 39 * texture_period)
			updateAnimationSpriteTexture(Thumanoid5_t, miniMap_t);

		if (_time > 39 * texture_period && _time <= 40 * texture_period)
			updateAnimationSpriteTexture(Thumanoid6_t, miniMap_t);

		if (_time > 40 * texture_period && _time <= 41 * texture_period)
			updateAnimationSpriteTexture(Thumanoid7_t, miniMap_t);

		if (_time > 41 * texture_period && _time <= 42 * texture_period)
			updateAnimationSpriteTexture(Thumanoid8_t, miniMap_t);

		if (_time > 42 * texture_period && _time <= 43 * texture_period)
			updateAnimationSpriteTexture(Thumanoid9_t, miniMap_t);

		if (_time > 43 * texture_period && _time <= 44 * texture_period)
			updateAnimationSpriteTexture(Thumanoid10_t, miniMap_t);

		if (_time > 44 * texture_period && _time <= 45 * texture_period)
			updateAnimationSpriteTexture(Thumanoid11_t, miniMap_t);

		if (_time > 45 * texture_period && _time <= 46 * texture_period)
			updateAnimationSpriteTexture(Thumanoid12_t, miniMap_t);

		if (_time > 46 * texture_period && _time <= 47 * texture_period)
			updateAnimationSpriteTexture(Thumanoid13_t, miniMap_t);

		if (_time > 47 * texture_period && _time <= 48 * texture_period)
			updateAnimationSpriteTexture(Thumanoid14_t, miniMap_t);

		if (_time > 48 * texture_period && _time <= 49 * texture_period)
			updateAnimationSpriteTexture(Thumanoid15_t, miniMap_t);

		if (_time > 49 * texture_period && _time <= 50 * texture_period)
			updateAnimationSpriteTexture(Thumanoid16_t, miniMap_t);

		if (_time > 50 * texture_period && _time <= 51 * texture_period)
			updateAnimationSpriteTexture(Thumanoid17_t, miniMap_t);

		if (_time > 51 * texture_period && _time <= 52 * texture_period)
			updateAnimationSpriteTexture(Thumanoid18_t, miniMap_t);

		if (_time > 52 * texture_period && _time <= 53 * texture_period)
			updateAnimationSpriteTexture(Thumanoid19_t, miniMap_t);

		if (_time > 53 * texture_period && _time <= 54 * texture_period)
			updateAnimationSpriteTexture(Thumanoid20_t, miniMap_t);

		if (_time > 54 * texture_period && _time <= 55 * texture_period)
			updateAnimationSpriteTexture(Thumanoid21_t, miniMap_t);

		if (_time > 55 * texture_period && _time <= 56 * texture_period)
			updateAnimationSpriteTexture(Thumanoid22_t, miniMap_t);

		if (_time > 56 * texture_period && _time <= 57 * texture_period)
			updateAnimationSpriteTexture(Thumanoid23_t, miniMap_t);

		if (_time > 57 * texture_period && _time <= 58 * texture_period)
			updateAnimationSpriteTexture(Thumanoid24_t, miniMap_t);

		if (_time > 58 * texture_period && _time <= 59 * texture_period)
			updateAnimationSpriteTexture(Thumanoid25_t, miniMap_t);

		if (_time > 59 * texture_period && _time <= 60 * texture_period)
			updateAnimationSpriteTexture(Thumanoid26_t, miniMap_t);

		if (_time > 60 * texture_period && _time <= 61 * texture_period)
			updateAnimationSpriteTexture(Thumanoid27_t, miniMap_t);

		if (_time > 61 * texture_period && _time <= 62 * texture_period)
			updateAnimationSpriteTexture(Thumanoid28_t, miniMap_t);

		return;
	}
}

void HumanoidSprite::walkingAndAbuction(std::string direction, std::shared_ptr<StopWatch>humanoid_watch)
{
	auto _time = humanoid_watch->time_elapsed();
	/*if (_time > 35 * texture_period)
		humanoid_watch->restart();*/
	
	if (direction == "left")
	{
		if (_time >= 0.0f && _time <= texture_period)
			updateSpriteTexture(humanoid1_t, miniMap_t);

		if (_time > texture_period && _time <= 2 * texture_period)
			updateSpriteTexture(humanoid2_t, miniMap_t);

		if (_time > 2 * texture_period && _time <= 3 * texture_period)
			updateSpriteTexture(humanoid3_t, miniMap_t);

		if (_time > 3 * texture_period && _time <= 4 * texture_period)
			updateSpriteTexture(humanoid4_t, miniMap_t);

		if (_time > 4 * texture_period && _time <= 5 * texture_period)
			updateSpriteTexture(humanoid5_t, miniMap_t);

		if (_time > 5 * texture_period && _time <= 6 * texture_period)
			updateSpriteTexture(humanoid6_t, miniMap_t);

		if (_time > 6 * texture_period && _time <= 7 * texture_period)
			updateSpriteTexture(humanoid7_t, miniMap_t);
		
		if (_time > 7 * texture_period && _time <= 8 * texture_period)
			updateSpriteTexture(humanoid8_t, miniMap_t);

		if (_time > 8 * texture_period && _time <= 9 * texture_period)
			updateSpriteTexture(humanoid9_t, miniMap_t);

		if (_time > 9 * texture_period && _time <= 10 * texture_period)
			updateSpriteTexture(humanoid10_t, miniMap_t);

		if (_time > 10 * texture_period && _time <= 11 * texture_period)
			updateSpriteTexture(humanoid11_t, miniMap_t);

		if (_time > 11 * texture_period && _time <= 12 * texture_period)
			updateSpriteTexture(humanoid12_t, miniMap_t);

		if (_time > 12 * texture_period && _time <= 13 * texture_period)
			updateSpriteTexture(humanoid13_t, miniMap_t);

		if (_time > 13 * texture_period && _time <= 14 * texture_period)
			updateSpriteTexture(humanoid14_t, miniMap_t);

		if (_time > 14 * texture_period && _time <= 15 * texture_period)
			updateSpriteTexture(humanoid15_t, miniMap_t);

		if (_time > 15 * texture_period && _time <= 16 * texture_period)
			updateSpriteTexture(humanoid16_t, miniMap_t);

		if (_time > 16 * texture_period && _time <= 17 * texture_period)
			updateSpriteTexture(humanoid17_t, miniMap_t);

		if (_time > 17 * texture_period && _time <= 18 * texture_period)
			updateSpriteTexture(humanoid18_t, miniMap_t);

		if (_time > 18 * texture_period && _time <= 19 * texture_period)
			updateSpriteTexture(humanoid19_t, miniMap_t);

		if (_time > 19 * texture_period && _time <= 20 * texture_period)
			updateSpriteTexture(humanoid20_t, miniMap_t);

		if (_time > 20 * texture_period && _time <= 21 * texture_period)
			updateSpriteTexture(humanoid21_t, miniMap_t);

		if (_time > 21 * texture_period && _time <= 22 * texture_period)
			updateSpriteTexture(humanoid22_t, miniMap_t);

		if (_time > 22 * texture_period && _time <= 23 * texture_period)
			updateSpriteTexture(humanoid23_t, miniMap_t);

		if (_time > 23 * texture_period && _time <= 24 * texture_period)
			updateSpriteTexture(humanoid24_t, miniMap_t);

		if (_time > 24 * texture_period && _time <= 25 * texture_period)
			updateSpriteTexture(humanoid25_t, miniMap_t);

		if (_time > 25 * texture_period && _time <= 26 * texture_period)
			updateSpriteTexture(humanoid26_t, miniMap_t);

		if (_time > 26 * texture_period && _time <= 27 * texture_period)
			updateSpriteTexture(humanoid27_t, miniMap_t);

		if (_time > 27 * texture_period && _time <= 28 * texture_period)
			updateSpriteTexture(humanoid28_t, miniMap_t);

		if (_time > 28 * texture_period && _time <= 29 * texture_period)
			updateSpriteTexture(humanoid29_t, miniMap_t);

		if (_time > 29 * texture_period && _time <= 30 * texture_period)
			updateSpriteTexture(humanoid30_t, miniMap_t);

		if (_time > 30 * texture_period && _time <= 31 * texture_period)
			updateSpriteTexture(humanoid31_t, miniMap_t);

		if (_time > 31 * texture_period && _time <= 32 * texture_period)
			updateSpriteTexture(humanoid32_t, miniMap_t);

		if (_time > 32 * texture_period && _time <= 33 * texture_period)
			updateSpriteTexture(humanoid33_t, miniMap_t);

		if (_time > 33 * texture_period && _time <= 34 * texture_period)
			updateSpriteTexture(humanoid34_t, miniMap_t);

		return;	
	}

	if (direction == "right")
	{
		if (_time >= 0.0f && _time <= texture_period)
			//updateSpriteTexture(humanoidRight1_t, miniMap_t);

		if (_time > texture_period && _time <= 2 * texture_period)
		{
			//updateSpriteTexture(humanoidRight2_t, miniMap_t);
			//humanoid_watch->restart();
		}
		return;
	}
}

void HumanoidSprite::falling(std::string direction, std::shared_ptr<StopWatch>humanoid_watch)
{
	texture_period = 0.1f;

	auto _time = humanoid_watch->time_elapsed();
	if (_time > 3 * texture_period)
		humanoid_watch->restart();
	
	if (_time >= 0.0f && _time <= texture_period)
		updateSpriteTexture(fallingHumanoid1_t, miniMap_t);

	if (_time > texture_period && _time <= 2 * texture_period)
	    updateSpriteTexture(fallingHumanoid2_t, miniMap_t);
	
	if (_time > 2 * texture_period && _time <= 3 * texture_period)
	{
		updateSpriteTexture(fallingHumanoid3_t, miniMap_t);
	}
}