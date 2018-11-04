#include "game.h" 



Game::Game()
	: m_window{ sf::VideoMode{ 1200, 800 }, "SFML" }		
{

	Player();

	player.createBoxPlayer(world);
	player.createSprite();

	PendulumTrap();
	pend.createBoxPend(world);
	pend.createSprite();
	

	GroundTexture.loadFromFile("ground.png");


	groundBox();
	createGround();

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
	player.updateSprite();
	pend.updateSprite();

}

void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(ground);


	player.render(m_window);

	pend.render(m_window);

	world.DrawDebugData();

	m_window.display();
}





void Game::groundBox()
{
	//************
	//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
	//************
	groundDef.position = b2Vec2(400 / SCALE, 700 /SCALE);
	groundDef.type = b2_staticBody;
	groundBody = world.CreateBody(&groundDef);

	groundShape.SetAsBox((1600.f / 2) / SCALE, (16.f / 2) / SCALE);
	groundFixtureDef.density = 1.0f;
	groundFixtureDef.friction = 0.7f;
	groundFixtureDef.shape = &groundShape;
	groundBody->CreateFixture(&groundFixtureDef);
}




void Game::createGround()
{
	ground.setTexture(GroundTexture);
	ground.setOrigin(400.f, 8.f);
	ground.setPosition(groundBody->GetPosition().x*SCALE, groundBody->GetPosition().y*SCALE);
}












