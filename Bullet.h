#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class Bullet
{
public:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	float speed = bulletSpeed;

	Bullet() : velocity(0.0f, 0.0f)
	{
		shape.setFillColor(sf::Color::Magenta);
		shape.setRadius(5);
	}
};