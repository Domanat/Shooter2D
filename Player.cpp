#include "Player.h"
#include <vector>

Player::Player() {}

Player::Player(int x, int y)
{
	shape = sf::CircleShape(20);
	shape.setPosition(x, y);
	shape.setFillColor(sf::Color::White);
	playerVelocity = sf::Vector2f(0.0f, 0.0f);
	sight.setSize(sf::Vector2f(30, 4));
	sight.setPosition(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());
	sight.setFillColor(sf::Color::Green);
}

void Player::update(float dt, sf::RenderWindow &window, vector<Enemy> &enemies)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && shape.getPosition().x + shape.getRadius() * 2 < windowWidth)
		playerVelocity.x = moveSpeed * dt;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && shape.getPosition().x > 0)
		playerVelocity.x = -moveSpeed * dt;
	else
		playerVelocity.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && shape.getPosition().y > 0)
		playerVelocity.y = -moveSpeed * dt;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && shape.getPosition().y + shape.getRadius() * 2 < windowHeight)
		playerVelocity.y = moveSpeed * dt;
	else
		playerVelocity.y = 0;


	//-------fcking magic---------------------
	sf::Vector2f sightDir;
	sightDir.x = mousePos.x - sight.getPosition().x;
	sightDir.y = mousePos.y - sight.getPosition().y;
	sf::Vector2f aimDirNorm = sightDir / sqrt(pow(sightDir.x, 2) + pow(sightDir.y, 2));
	//----------------------------------------


	float rotation = (atan2(mousePos.y - sight.getPosition().y, mousePos.x - sight.getPosition().x)) * 180 / PI;
	//-------checking for only one click-------------------------
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!isShooting) {
			mousePos = sf::Mouse::getPosition();
			isShooting = true;

			Bullet bullet;
			bullet.shape.setPosition(sf::Vector2f(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius()));
			bullet.velocity = aimDirNorm * bullet.speed * dt;

			bullets.push_back(Bullet(bullet));
		}
	}
	else {
		isShooting = false;
	}

	//-------------set aim line---------------------
	sight.setRotation(rotation);

	shape.move(playerVelocity);
	sight.move(playerVelocity);

	//-------check collision with enemies---------------
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].shape.move(bullets[i].velocity);

		//---------delete bullets if it out of bounds----------------
		if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > windowWidth ||
			bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > windowHeight)
		{
			bullets.erase(bullets.begin() + i);
			continue;
		}
		//--------if bullet collide with enemy delete both--------------------
		for (int j = 0; j < enemies.size(); j++)
		{
			if (collideEnemy(bullets[i], enemies[j]))
			{
				bullets.erase(bullets.begin() + i);
				enemies.erase(enemies.begin() + j);
				continue;
			}			
		}
	}		
}

void Player::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < bullets.size(); i++)
		window.draw(bullets[i].shape);

	window.draw(shape);
	window.draw(sight);
}

bool Player::collideEnemy(Bullet bullet, Enemy enemy)
{
	double distX = (enemy.shape.getPosition().x + enemy.shape.getRadius()) - (bullet.shape.getPosition().x + bullet.shape.getRadius());
	double distY = (enemy.shape.getPosition().y + enemy.shape.getRadius()) - (bullet.shape.getPosition().y + bullet.shape.getRadius());

	double distance = sqrt(pow(distX, 2) + pow(distY, 2));

	if (distance < enemy.shape.getRadius() + bullet.shape.getRadius())
		return true;

	return false;
}

bool Player::collideEnemy(Enemy enemy)
{
	double distX = (enemy.shape.getPosition().x) - (shape.getPosition().x);
	double distY = (enemy.shape.getPosition().y) - (shape.getPosition().y);

	double distance = sqrt(pow(distX, 2) + pow(distY, 2));

	if (distance < enemy.shape.getRadius() * 2)
		return true;

	return false;
}
