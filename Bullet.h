#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Enemy.h"

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

	bool collideEnemy(Enemy enemy)
	{
		double distX = (enemy.shape.getPosition().x + enemy.shape.getRadius()) - (shape.getPosition().x + shape.getRadius());
		double distY = (enemy.shape.getPosition().y + enemy.shape.getRadius()) - (shape.getPosition().y + shape.getRadius());

		double distance = sqrt(pow(distX, 2) + pow(distY, 2));

		if (distance < enemy.shape.getRadius() + shape.getRadius())
			return true;

		return false;
	}

	//void wallCollision(Wall wall) {}
};