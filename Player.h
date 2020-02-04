#pragma once
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class Player
{
public:
	sf::CircleShape shape;
	sf::Vector2f pVelocity;
	sf::Vector2f bVelocity;
	sf::RectangleShape line;
	bool isShooting = false;
	vector<sf::RectangleShape> bullets;

	Player(int x, int y)
	{
		shape = sf::CircleShape(20);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::White); 
		pVelocity = sf::Vector2f(0.0f, 0.0f);
		line.setSize(sf::Vector2f(2, 1500));
		line.setPosition(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());
		line.setFillColor(sf::Color::Green);
	}

	void update(float dt, sf::RenderWindow &window)
	{

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && shape.getPosition().x + shape.getRadius() * 2 < windowWidth)
			pVelocity.x = speed * dt;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shape.getPosition().x > 0)
			pVelocity.x = -speed * dt;
		else
			pVelocity.x = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && shape.getPosition().y > 0)
			pVelocity.y = -speed * dt;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)&& shape.getPosition().y + shape.getRadius() * 2 < windowHeight)
			pVelocity.y = speed * dt;
		else
			pVelocity.y = 0;

		//-------checking for only one click-------------------------
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!isShooting) {
				mousePos = sf::Mouse::getPosition();
				isShooting = true;

				sf::RectangleShape bullet;
				bullet.setSize(sf::Vector2f(4, 2));
				bullet.setPosition(sf::Vector2f(line.getPosition().x, line.getPosition().y));
				bullet.setFillColor(sf::Color::Magenta);
				bullets.push_back(bullet);
			}
		}
		else {
			isShooting = false;
		}

		float rotation = (atan2(mousePos.x - line.getPosition().x, mousePos.y - line.getPosition().y)) * 180 / PI;

		//-------------set aim---------------------
		line.setRotation(-rotation);

		shape.move(pVelocity);
		line.move(pVelocity);
	
		//for (int i = 0; i < bullets.size(); i++)
		//	bullets[i].move(bVelocity);

		//cout << line.getPosition().x << " : " << line.getPosition().x + line.getSize().x << endl;
		cout << line.getRotation() << endl;
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(shape);
		window.draw(line);
		for (int i = 0; i < bullets.size(); i++)
			window.draw(bullets[i]);
	}
};