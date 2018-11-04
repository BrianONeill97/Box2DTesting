#pragma once
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include <iostream>
class PendulumTrap
{
public:
	PendulumTrap();
	~PendulumTrap();

	void render(sf::RenderWindow &window);

	/** We need this to easily convert between pixel and real-world coordinates*/
	const float SCALE = 30.f;

	sf::Sprite m_pendSprite;
	sf::Texture pendTexture;

	//Player
	b2BodyDef pendBodyDef;
	b2Body* pendBody;
	b2PolygonShape shape;
	b2FixtureDef pendFixtureDef;

	void createBoxPend(b2World &world);
	void createSprite();
	void updateSprite();



	void pendMovement(b2Body * pBody, double speed);

};

