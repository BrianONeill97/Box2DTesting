#ifndef GAME
#define GAME


#include "Box2D/Box2D.h"
#include "SFML/Graphics.hpp"
#include "b2GLDraw.h"
#include <iostream>
#include "Player.h"

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
	//font for the text
	sf::Font m_font;


	//Sprites
	sf::Sprite ground;
	sf::Texture GroundTexture;

	sf::Sprite m_sprite;
	sf::Texture boxTexture;


	Player player;
	

	/** We need this to easily convert between pixel and real-world coordinates*/
	const float SCALE = 30.f;

	//World
	b2Vec2 gravity = { 0.0f,9.8f };
	b2World world{gravity};
	float32 timeStep = 1 / 60.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position
	b2GLDraw fooDrawInstance;

	 
	 
	

	 //Ground
	 b2BodyDef groundDef;
	 b2Body* groundBody;
	 b2PolygonShape groundShape;
	 b2FixtureDef groundFixtureDef;


	 void createGround();
	 void groundBox();





};
#endif


