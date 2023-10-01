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

	miniMap_t.loadFromFile("resources/minimap.png");
	miniMap_s.setTexture(miniMap_t);
	auto windowWidth = 800.0f;
	miniMapPosition.x = windowWidth / 2.0f;
	miniMapPosition.y = 51.0f;
	miniMap_s.setOrigin(400.0f, 50.0f);
	miniMap_s.setPosition(miniMapPosition);

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

void Minimap::updateCamera(std::shared_ptr<Player>& player, std::shared_ptr<sf::RenderWindow>& window)
{
	auto [playerXpos, playerYpos] = player->getPlayerPosition();
	viewCenter.x = playerXpos;
	miniMapView.setCenter((viewCenter.x - mapOffset) * scalingFactor, viewCenter.y);
}
