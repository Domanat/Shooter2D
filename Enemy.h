#ifndef ENEMY
#define ENEMY

#include <SFML/Graphics.hpp>
#include "Constants.h"


class Enemy
{
public:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	//float speed;

	Enemy(int x, int y)
	{
		shape.setFillColor(sf::Color::Red);
		shape.setRadius(20);
		shape.setPosition(x, y);
		velocity.x = 0.0f;
		velocity.y = 0.0f;
	}

	Enemy() {}

	void update(float dt) 
	{

	}

	
};

#endif