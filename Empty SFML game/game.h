#pragma once
// Author = Brian O'Neill
// Date = 15/10/2017
//Student number = C00213756
// Time taken = 4 hours
//Known Issues = Text is only drawn to screen one for a few seconds then disappears and does not redraw
//					also controller is connected text is commented out as when it is not it is constantly output
#ifndef GAME
#define GAME



#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"



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

	//Sprites
	sf::Texture GroundTexture;
	sf::Texture CircleTexture;

	sf::Sprite ballSprite;
	sf::Sprite ground;

	void createSprite();
	void createGround();

	//Box2D
	void createBody();
	b2Vec2 gravity;
	b2World *world;

	

	/** We need this to easily convert between pixel and real-world coordinates*/
	 const float SCALE = 30.f;

	/** Create the base for the boxes to land */
	void CreateGround(b2World& World, float X, float Y);

	/** Create the boxes */
	void CreateBox(b2World& World, int MouseX, int MouseY);


};

#endif // !GAME

