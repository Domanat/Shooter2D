#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "Player.h"

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Shooter");
	Player p(windowWidth/2, windowHeight/2);

	sf::Clock clock;
	sf::RectangleShape line;
	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		//-----------------Update player--------------------
		p.update(dt, window);

		window.clear();
		//-----------------Draw objects--------------------
		p.draw(window);
		window.display();
	}

	return 0;
}