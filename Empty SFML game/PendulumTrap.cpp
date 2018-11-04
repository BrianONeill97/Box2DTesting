#include "PendulumTrap.h"



PendulumTrap::PendulumTrap()
{
	pendTexture.loadFromFile("pendTrap.png");
}


PendulumTrap::~PendulumTrap()
{
}


void PendulumTrap::createBoxPend(b2World & world)
{
	//************
//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
//************
	pendBodyDef.position = b2Vec2(500 / SCALE, 500 / SCALE);
	pendBodyDef.type = b2_dynamicBody;
	pendBody = world.CreateBody(&pendBodyDef);

	shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	pendFixtureDef.density = 1.0f;
	pendFixtureDef.shape = &shape;
	pendBody->CreateFixture(&pendFixtureDef);
	pendBody->SetGravityScale(0);


}

void PendulumTrap::createSprite()
{
	m_pendSprite.setTexture(pendTexture);
	m_pendSprite.setOrigin(50.f, 100.f);
	//m_sprite.scale(0.5, 0.5);
	m_pendSprite.setPosition(pendBody->GetPosition().x * SCALE, pendBody->GetPosition().y*SCALE);
}

void PendulumTrap::updateSprite()
{
	pendMovement(pendBody, 0.2);

	//Setting Positions and rotations after movement
	m_pendSprite.setPosition(pendBody->GetPosition().x * SCALE, pendBody->GetPosition().y*SCALE);
	m_pendSprite.setRotation(pendBody->GetAngle() * 180 / b2_pi);
}

void PendulumTrap::pendMovement(b2Body * pBody, double speed)
{
	if(pendBody->GetAngle() < 160)
	{	
		pBody->ApplyTorque(speed, true);

	}
	else
	{
		pBody->ApplyTorque(-speed, true);
	}


	std::cout << m_pendSprite.getRotation() << std::endl;
}

void PendulumTrap::render(sf::RenderWindow & window)
{
	window.draw(m_pendSprite);
}
