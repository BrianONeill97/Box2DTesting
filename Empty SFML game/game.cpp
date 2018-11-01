#include "game.h" 


b2Vec2 gravity = { 0.0f,9.8f };
b2World world(gravity);

Game::Game()
	: m_window{ sf::VideoMode{ 1200, 800 }, "SFML" }		
{
	m_jumpTimer = 0;


	b2Vec2 gravity = { 0.0f,9.8f };
	b2World world(gravity);
	
	boxTexture.loadFromFile("box.png");
	GroundTexture.loadFromFile("ground.png");

	if (!GroundTexture.loadFromFile("ground.png"))
	{
		std::cout << "error loading from file ";
	}

	createBoxPlayer();
	groundBox();
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


	


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		moveRight(playerBody);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		moveLeft(playerBody);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_jumpTimer > 0)
		{
			return;
		}
		else
		{
			moveUp(playerBody);
		
			m_jumpTimer = 100;
		}
		
	}


	
		m_jumpTimer--;
	

	

	updateSprite();
}

void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(ground);

	m_window.draw(m_sprite);



	world.DrawDebugData();

	m_window.display();
}





void Game::createBoxPlayer()
{
	//************
	//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
	//************
	bodyDef.position = b2Vec2(300 / SCALE , 500 / SCALE );
	bodyDef.type = b2_dynamicBody;
	playerBody = world.CreateBody(&bodyDef);

	shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.shape = &shape;
	playerBody->CreateFixture(&fixtureDef);


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


void Game::createSprite()
{
	m_sprite.setTexture(boxTexture);
	m_sprite.setOrigin(16.f, 16.f);
	//m_sprite.scale(0.5, 0.5);
	m_sprite.setPosition(playerBody->GetPosition().x * SCALE, playerBody->GetPosition().y*SCALE);
}

void Game::updateSprite()
{
	m_sprite.setPosition(playerBody->GetPosition().x * SCALE, playerBody->GetPosition().y * SCALE);
	m_sprite.setRotation(playerBody->GetAngle() * 180 / b2_pi);
}

void Game::createGround()
{

	ground.setTexture(GroundTexture);
	ground.setOrigin(400.f, 8.f);
	ground.setPosition(groundBody->GetPosition().x*SCALE, groundBody->GetPosition().y*SCALE);
}

void Game::moveRight(b2Body * body)
{
	body->ApplyLinearImpulse(b2Vec2(0.4, 0), body->GetWorldCenter(), true);
}

void Game::moveLeft(b2Body * body)
{
	body->ApplyLinearImpulse(b2Vec2(-0.4, 0), body->GetWorldCenter(), true);

}

void Game::moveUp(b2Body * body)
{
	body->ApplyLinearImpulse(b2Vec2(0, -15), body->GetWorldCenter(), true);

}










