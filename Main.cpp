#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Constants.h"
#include <vector>


using namespace std;

int main()
{
	sf::RenderWindow window;
	Player player(windowWidth / 2, windowHeight / 2);

	Enemy enemy(400, 400);
	
	vector<Enemy> enemies;
	enemies.push_back(enemy);
	enemies.push_back(Enemy(100, 100));
	
	window.create(sf::VideoMode(windowWidth, windowHeight), "Shooter");
	window.setFramerateLimit(60);
	//player = Player(windowWidth / 2, windowHeight / 2);
	//enemy = Enemy(400, 400);

	sf::Clock clock;
	while (window.isOpen())
	{

		float dt = clock.restart().asSeconds();

		//-----------------input-----------------------
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			//TODO: add player's input
		}
		//-----------------Update objects------------------
		player.update(dt, window, enemies);
		enemy.update(dt);

		//-----------------Draw objects--------------------
		window.clear();
		//--------draw player----------------------

		player.draw(window);

		//------------------------------------------

		//-------draw enemies-----------------------
		for (int i = 0; i < enemies.size(); i++)
			window.draw(enemies[i].shape);

		//-------draw walls---------------------------
		

		window.display();
	}

	return 0;
}


