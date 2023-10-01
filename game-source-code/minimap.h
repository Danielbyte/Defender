#ifndef MINIMAP_H
#define MINIMAP_H

#include <SFML/Graphics.hpp>
#include "player.h"
#include "playerSprite.h"
#include "lander.h"
#include "landerSprite.h"
#include "humanoid.h"
#include "humanoidSprite.h"

class Minimap
{
public:
	Minimap();
	void update(std::shared_ptr<Player>& player);

private:
	void updateLandscape(std::shared_ptr<Player>& player);
	float scalingFactor;
	float mapOffset;
	sf::Vector2f highLighterSize; //highlights the main game section
	//Mini-map views
	sf::View miniMapView;
	sf::Vector2f miniMapViewSize;
	sf::Vector2f viewCenter;

	sf::Vector2f miniMapPosition;
	sf::Texture miniMap_t;
	sf::Sprite miniMap_s;

	sf::Texture miniMainSection_t;
	sf::Sprite miniMainSection_s;
	sf::Vector2f gameSectionPosition;


	sf::Texture miniTerrain1_t;
	sf::Vector2f t1Pos;
	sf::Sprite miniTerrain1_s;
	sf::Texture miniTerrain2_t;
	sf::Sprite miniTerrain2_s;
	sf::Vector2f t2Pos;
};
#endif // !MINIMAP_H

