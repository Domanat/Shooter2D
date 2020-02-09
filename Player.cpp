#include "Player.h"
#include <vector>

Player::Player() 
{
	shape = sf::CircleShape(20);
	shape.setPosition(windowWidth/2, windowHeight/2);
	shape.setFillColor(sf::Color::White);
	velocity = sf::Vector2f(0.0f, 0.0f);
	sight.setSize(sf::Vector2f(30, 4));
	sight.setPosition(shape.getPosition().x + shape.getRadius(), shape.getPosition().y + shape.getRadius());
	sight.setFillColor(sf::Color::Green);
}

void Player::update(float dt, sf::RenderWindow &window, vector<Enemy> &enemies)
{
	if (moveRight && shape.getPosition().x + shape.getRadius() * 2 < windowWidth)
		velocity.x = moveSpeed * dt;
	else if (moveLeft && shape.getPosition().x > 0)
		velocity.x = -moveSpeed * dt;
	else
		velocity.x = 0;


	if (moveUp && shape.getPosition().y > 0)
		velocity.y = -moveSpeed * dt;
	else if (moveDown && shape.getPosition().y + shape.getRadius() * 2 < windowHeight)
		velocity.y = moveSpeed * dt;
	else
		velocity.y = 0;
		
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

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

	shape.move(velocity);
	sight.move(velocity);
		
	collide(bullets, enemies);
}

//--------checking collision with objects--------------------
void Player::collide(vector<Bullet> &bullets, vector<Enemy> &enemies)
{
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
			if (bullets[i].collideEnemy(enemies[j]))
			{
				bullets.erase(bullets.begin() + i);
				enemies.erase(enemies.begin() + j);
				break;
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

//-----------check player's collision with enemy
bool Player::collideEnemy(Enemy enemy)
{
	double distX = (enemy.shape.getPosition().x) - (shape.getPosition().x);
	double distY = (enemy.shape.getPosition().y) - (shape.getPosition().y);

	double distance = sqrt(pow(distX, 2) + pow(distY, 2));

	if (distance < enemy.shape.getRadius() * 2)
		return true;

	return false;
}


void Player::goRight()
{
	moveRight = true;
}

void Player::stopRight()
{
	moveRight = false;
}

void Player::goLeft()
{
	moveLeft = true;
}

void Player::stopLeft()
{
	moveLeft = false;
}

void Player::goDown()
{
	moveDown = true;
}

void Player::goUp()
{
	moveUp = true;
}

void Player::stopUp()
{
	moveUp = false;
}

void Player::stopDown()
{
	moveDown = false;
}