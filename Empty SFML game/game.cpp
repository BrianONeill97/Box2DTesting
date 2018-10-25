#include "game.h" 
#include <iostream> 

b2Vec2 Gravity(0.f, 9.8f);
b2World World(Gravity);

Game::Game()
	: m_window{ sf::VideoMode{ 1200, 800 }, "SFML" }		
{



	CircleTexture.loadFromFile("ball.png");


	GroundTexture.loadFromFile("ground.png");


	createSprite();
	createBody();
	createGround();

	createGroundBox(World, 0, 500);

	

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		loadContent();
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
			World.DrawDebugData();
		}
		render();
	}
}

void Game::loadContent()
{

}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	
	}
}

void Game::update(sf::Time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		CreateBox(World, sPos.x, sPos.y);
	}
	
	World.Step(1 / 60.f,8,3);
}

void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(ballSprite);

	m_window.draw(ground);

	
	m_window.display();
}

void Game::createSprite()
{
	ballSprite.setTexture(CircleTexture);
	ballSprite.setOrigin(97.5f, 97.5f);
	ballSprite.scale(0.4, 0.4);
	ballSprite.setPosition(sPos.x,sPos.y);

}

void Game::createGround()
{
	ground.setTexture(GroundTexture);
	ground.setPosition(0, 120);
	ground.scale(1.2, 1);
}

void Game::createBody()
{


}

void Game::updatePlayer(b2World worldR)
{
}

void Game::createGroundBox(b2World & World, float X, float Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_staticBody; // so its not effected by forces
	b2Body* body = World.CreateBody(&BodyDef);


	b2PolygonShape Shape;
	Shape.SetAsBox((1200.f / 2) / SCALE, (16.f / 2) / SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.f;
	fixtureDef.shape = &Shape;
	body->CreateFixture(&fixtureDef);
	
}

void Game::CreateBox(b2World & World, int X, int Y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}
