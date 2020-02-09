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
private:
	bool moveRight;
	bool moveLeft;
	bool moveDown;
	bool moveUp;

public:

	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::RectangleShape sight;
	bool isShooting = false;
	vector<Bullet> bullets;

	Player();

	void update(float dt, sf::RenderWindow &window, vector<Enemy> &enemies);
	void draw(sf::RenderWindow &window);

	void collide(vector<Bullet> &bullets, vector<Enemy> &enemies);
	bool collideEnemy(Enemy enemy);


	void goRight();
	void stopRight();
	void stopLeft();
	void goLeft();
	void goUp();
	void goDown();
	void stopUp();
	void stopDown();
};
#endif
