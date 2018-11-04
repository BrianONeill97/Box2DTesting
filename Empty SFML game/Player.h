#pragma once
#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"

class Player
{
public:
	Player();
	~Player();
	void render(sf::RenderWindow &window);

	/** We need this to easily convert between pixel and real-world coordinates*/
	const float SCALE = 30.f;

	sf::Sprite m_sprite;
	sf::Texture boxTexture;

	//Player
	b2BodyDef bodyDef;
	b2Body* playerBody;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

	//Cooldowns
	int m_jumpTimer;
	int m_dashTimer;

	//Jumping
	bool jumped;
	int jumpCount;
	int MAX_JUMPS = 2;

	//Speeds
	b2Vec2 speed = { 0.3, 0 };
	b2Vec2 dashSpeed = { 20, 0 };
	b2Vec2 jumpHeight = { 0,-10 };

	//Creates and Updates Sprite
	void createBoxPlayer(b2World &world);
	void createSprite();
	void updateSprite();




	//Movement 
	void moveRight(b2Body *body);
	bool movingRight;
	void moveLeft(b2Body *body);
	bool movingLeft;
	void moveUp(b2Body *body);
	void dash(b2Body *body);
};

