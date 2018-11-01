#include "game.h" 


b2Vec2 gravity = { 0.0f,9.8f };
b2World world(gravity);

Game::Game()
	: m_window{ sf::VideoMode{ 1200, 800 }, "SFML" }		
{

	b2Vec2 gravity = { 0.0f,9.8f };
	b2World world(gravity);
	
	CircleTexture.loadFromFile("ball.png");
	GroundTexture.loadFromFile("ground.png");

	if (!GroundTexture.loadFromFile("ground.png"))
	{
		std::cout << "error loading from file ";
	}

	createBoxPlayer();
	createSprite();
	createGround();

	b2GLDraw fooDrawInstance;
	world.SetDebugDraw(&fooDrawInstance);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	fooDrawInstance.SetFlags(flags);

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
	world.Step(timeStep, velocityIterations, positionIterations);

	

	updateSprite();


	


}

void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_sprite);

	m_window.draw(ground);

	world.DrawDebugData();

	m_window.display();
}





void Game::createBoxPlayer()
{


	bodyDef.position = b2Vec2(300 , 100 );
	bodyDef.type = b2_dynamicBody;
	playerBody = world.CreateBody(&bodyDef);

	shape.SetAsBox((500.0f / 2) / SCALE, (500.0f / 2) / SCALE);
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.shape = &shape;
	playerBody->CreateFixture(&fixtureDef);


}

void Game::groundBox()
{
	groundDef.position = b2Vec2(0, 320);
	groundDef.type = b2_staticBody;
	groundBody = world.CreateBody(&groundDef);

	groundShape.SetAsBox((1000.0f / 2) / SCALE, (100.0f / 2) / SCALE);
	groundFixtureDef.density = 1.0f;
	groundFixtureDef.friction = 0.7f;
	groundFixtureDef.shape = &groundShape;
	groundBody->CreateFixture(&groundFixtureDef);
}

void Game::createSprite()
{
	m_sprite.setTexture(CircleTexture);
	m_sprite.setOrigin(8.f, 8.0f);
	m_sprite.scale(0.5, 0.5);
	m_sprite.setPosition(playerBody->GetPosition().x, playerBody->GetPosition().y);
}

void Game::updateSprite()
{
	m_sprite.setPosition(playerBody->GetPosition().x, playerBody->GetPosition().y);
	m_sprite.setRotation(playerBody->GetAngle() * 180 / b2_pi);
}

void Game::createGround()
{
	ground.setTexture(GroundTexture);
//	ground.setPosition(groundBody->GetPosition().x, groundBody->GetPosition().y);
}








