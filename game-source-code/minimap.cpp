#include "minimap.h"

Minimap::Minimap():
	scalingFactor{0.5f},
	mapOffset{400.0f}
{
	highLighterSize.x = 400.0f;
	highLighterSize.y = 100.0f;

	miniMapViewSize.x = 800.0f;
	miniMapViewSize.y = 600.0f;
	viewCenter.x = 400.0f;
	auto windowHeight = 600.0f;
	viewCenter.y = windowHeight / 2.0f;

	miniMapView.setSize(miniMapViewSize);
	miniMapView.setCenter(viewCenter);
	miniMapView.setViewport(sf::FloatRect(0.3125f, 0.0f, 0.375f, 1.0f));

	miniTerrain1_t.loadFromFile("resources/terrain-1-mini.png");
	miniTerrain1_s.setTexture(miniTerrain1_t);
	miniTerrain1_s.setOrigin(800.0f, 30 / 2.0f);
	t1Pos.x = 700.0f;
	t1Pos.y = 85.0f;
	miniTerrain1_s.setPosition(t1Pos);

	miniTerrain2_t.loadFromFile("resources/terrain-2-mini.png");
	miniTerrain2_s.setTexture(miniTerrain2_t);
	miniTerrain2_s.setOrigin(800.0f, 30 / 2.0f);
	t2Pos.x = -900.0f;
	t2Pos.y = 85.0f;
	miniTerrain2_s.setPosition(t2Pos);

	miniMainSection_t.loadFromFile("resources/miniMainSection.png");
	miniMainSection_s.setTexture(miniMainSection_t);
	miniMainSection_s.setOrigin(highLighterSize / 2.0f);
	gameSectionPosition.x = 0.0f;
	gameSectionPosition.y = 51.0f;
	miniMainSection_s.setPosition(0.0f, 51);
}

void Minimap::update(std::shared_ptr<Player>& player)
{
	auto [playerXpos, playerYpos] = player->getPlayerPosition();
	viewCenter.x = playerXpos;
	miniMapView.setCenter((viewCenter.x - mapOffset) * scalingFactor, viewCenter.y);

	gameSectionPosition.x = (viewCenter.x - mapOffset) * scalingFactor;
	miniMainSection_s.setPosition(gameSectionPosition);

	updateLandscape(player);
}

void Minimap::updateLandscape(std::shared_ptr<Player>& player)
{
	auto [playerXpos, playerYpos] = player->getPlayerPosition();
	auto backgroundWidth = 1600.0f;
	auto scalingFactor = 0.5f;
	auto scaledPlayerXpos = playerXpos * scalingFactor;

	auto distance1 = abs(scaledPlayerXpos - t1Pos.x);
	auto distance2 = abs(scaledPlayerXpos - t2Pos.x);
	auto playerDirection = player->getDirection();

	if (distance2 > distance1)
	{
		if (playerDirection == "right")
		{
			if (scaledPlayerXpos >= t1Pos.x)
				t2Pos.x = t1Pos.x + backgroundWidth;

			miniTerrain2_s.setPosition(t2Pos);
			return;
		}

		if (scaledPlayerXpos <= t1Pos.x)
			t2Pos.x = t1Pos.x - backgroundWidth;

		miniTerrain2_s.setPosition(t2Pos);
		return;
	}

	if (distance1 > distance2)
	{
		if (playerDirection == "right")
		{
			if (scaledPlayerXpos >= t2Pos.x)
				t1Pos.x = t2Pos.x + backgroundWidth;

			miniTerrain1_s.setPosition(t1Pos);
			return;
		}

		if (scaledPlayerXpos <= t2Pos.x)
			t1Pos.x = t2Pos.x - backgroundWidth;

		miniTerrain1_s.setPosition(t1Pos);
	}
}

void Minimap::drawMiniMap(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<PlayerSprite>& player_icon, std::vector<std::shared_ptr<LanderSprite>>& lander_sprites)
{
	window->setView(miniMapView);
	window->draw(miniTerrain1_s);
	window->draw(miniTerrain2_s);
	window->draw(miniMainSection_s);
	window->draw(player_icon->getMiniSprite());

	for (auto& lander_icon : lander_sprites)
		window->draw(lander_icon->getMiniSprite());
}
