#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Constants.h"
#include <vector>
using namespace std;

class Game
{

public:
	Player player;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RenderWindow window;
	vector<Enemy> enemies;

	Game()
	{
		texture.loadFromFile("background.jpg");
		sprite.setTexture(texture);
		for (int i = 0; i < 5; i++)
		{
			enemies.push_back(Enemy(100 + i * 50, 100));
			enemies.push_back(Enemy(100, 100 + i * 100));
		}

		window.create(sf::VideoMode(windowWidth, windowHeight), "Shooter");
		window.setFramerateLimit(60);
	}

	void start();
	void input();
	void update(float dt);
	void draw();
};

void Game::start()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();
		//-----------------Input from player----------------
		input();
		//-----------------Update objects------------------
		update(dt);
		//-----------------Draw Objects------------------
		draw();
	}
}

void Game::input()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player.goRight();
	else
		player.stopRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player.goLeft();
	else
		player.stopLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player.goUp();
	else
		player.stopUp();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player.goDown();
	else
		player.stopDown();
	
}

void Game::update(float dt)
{
	player.update(dt, window, enemies);
}


void Game::draw()
{
	window.clear();
	player.draw(window);

	for (Enemy m : enemies)
		window.draw(m.shape);

	window.draw(sprite);
	window.display();
}


int main()
{
	Game game;
	
	game.start();

	return 0;
}

