#ifndef GAME
#define GAME


#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "b2GLDraw.h"
#include <iostream>

class Game
{
public:
	Game();
	void run();
private:
	void			 loadContent();
	void             processEvents();
	void             update(sf::Time);
	void             render();


private:
	sf::RenderWindow m_window;
	//texture for the screen
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	//font for the text
	sf::Font m_font;
	//EVENT
	sf::Event event;

	//Sprites
	sf::Texture GroundTexture;
	sf::Texture boxTexture;

	sf::Sprite boxSprite;
	sf::Sprite ground;



	/** We need this to easily convert between pixel and real-world coordinates*/
	const float SCALE = 30.f;

	//World


	b2Vec2 gravity = { 0.0f,9.8f };
	b2World world{gravity};

	 float32 timeStep = 1 / 60.0;      //the length of time passed to simulate (seconds)
	 int32 velocityIterations = 8;   //how strongly to correct velocity
	 int32 positionIterations = 3;   //how strongly to correct position

	 b2GLDraw fooDrawInstance;

	 
	 
	 //Player
	 b2BodyDef bodyDef;
	 b2Body* playerBody;
	 b2PolygonShape shape;
	 b2FixtureDef fixtureDef;

	 int m_jumpTimer;
	 bool jumped;

	 //Ground
	 b2BodyDef groundDef;
	 b2Body* groundBody;
	 b2PolygonShape groundShape;
	 b2FixtureDef groundFixtureDef;

	 void createBoxPlayer();
	 void createSprite();

	 void updateSprite();

	 void createGround();
	 void groundBox();

	 //Movement 
	 void moveRight(b2Body *body);
	 void moveLeft(b2Body *body);
	 void moveUp(b2Body *body);




};
#endif


