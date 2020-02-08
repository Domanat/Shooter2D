#ifndef PLAYER
#define PLAYER
#include <iostream>
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <vector>

using namespace std;

class Player
{
public:

	sf::CircleShape shape;
	sf::Vector2f playerVelocity;
	sf::RectangleShape sight;
	bool isShooting = false;
	vector<Bullet> bullets;

	Player();
	Player(int x, int y);

	void update(float dt, sf::RenderWindow &window, vector<Enemy> &enemies);
	void draw(sf::RenderWindow &window);

	bool collideEnemy(Bullet bullet, Enemy enemy);
	bool collideEnemy(Enemy enemy);
};
#endif
