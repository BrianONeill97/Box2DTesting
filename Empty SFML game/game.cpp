#include "game.h" 
#include <iostream> 

Game::Game()
	: m_window{ sf::VideoMode{ 800, 600 }, "SFML" }		
{
	gravity = { 0.f, 9.8f };
	this->world = new b2World(gravity);


	CircleTexture.loadFromFile("ball.png");


	GroundTexture.loadFromFile("ground.png");


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
	createSprite();
	createBody();
	createGround();
	
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
	ballSprite.setOrigin(16.f, 16.f);
	ballSprite.setPosition(200,200);

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

void Game::CreateGround(b2World & World, float X, float Y)
{
}

void Game::CreateBox(b2World & World, int MouseX, int MouseY)
{
}
