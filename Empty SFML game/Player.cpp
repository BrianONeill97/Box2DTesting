#include "Player.h"



Player::Player()
{
	m_jumpTimer = 0;
	m_dashTimer = 0;
	jumpCount = 0;
	boxTexture.loadFromFile("box.png");
}


Player::~Player()
{
}


void Player::createBoxPlayer(b2World  &world)
{
	//************
//When dividing the SetAsBox by scale you MUST multiply GetPosition() by SCALE
//************
	bodyDef.position = b2Vec2(300 / SCALE, 500 / SCALE);
	bodyDef.type = b2_dynamicBody;
	playerBody = world.CreateBody(&bodyDef);

	shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.7f;
	fixtureDef.shape = &shape;
	playerBody->CreateFixture(&fixtureDef);
}

void Player::createSprite()
{
	m_sprite.setTexture(boxTexture);
	m_sprite.setOrigin(16.f, 16.f);
	//m_sprite.scale(0.5, 0.5);
	m_sprite.setPosition(playerBody->GetPosition().x * SCALE, playerBody->GetPosition().y*SCALE);
}

void Player::updateSprite()
{
//Moving Left to right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveRight(playerBody);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveLeft(playerBody);
	}


///Jumping
	if (jumpCount < MAX_JUMPS)
	{
		if (m_jumpTimer <= 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				moveUp(playerBody);
				m_jumpTimer = 50;
				jumpCount += 1;
			}
		}
	}

	if (playerBody->GetLinearVelocity().y == 0)
	{
		jumpCount = 0;
	}



///Dashing
	if (m_dashTimer <= 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			dash(playerBody);
			m_dashTimer = 100;
		}
	}



//Cooldowns
	m_jumpTimer--;
	m_dashTimer--;

//Setting Positions and rotations after movement
	m_sprite.setPosition(playerBody->GetPosition().x * SCALE, playerBody->GetPosition().y * SCALE);
	m_sprite.setRotation(playerBody->GetAngle() * 180 / b2_pi);
}

void Player::render(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

void Player::moveRight(b2Body * body)
{
	body->ApplyLinearImpulse(speed, body->GetWorldCenter(), true);
	movingRight = true;
	movingLeft = false;
}

void Player::moveLeft(b2Body * body)
{
	body->ApplyLinearImpulse(-speed, body->GetWorldCenter(), true);
	movingRight = false;
	movingLeft = true;

}

void Player::moveUp(b2Body * body)
{
	body->ApplyLinearImpulse(jumpHeight, body->GetWorldCenter(), true);
}

void Player::dash(b2Body * body)
{
	if (movingLeft == true)
	{
		body->ApplyLinearImpulse(-dashSpeed, body->GetWorldCenter(), true);
	}
	if (movingRight == true)
	{	
			body->ApplyLinearImpulse(dashSpeed, body->GetWorldCenter(), true);
	}

}
