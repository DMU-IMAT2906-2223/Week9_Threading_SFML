#include<iostream>
#include<string>
#include <future> /**Used for std::async, std::future**/
#include <thread> /**For use with threads. **/
#include <chrono>
#include "FileProcess.h"
#include <SFML/Graphics.hpp>


//Function for drawing a SFML circle
sf::CircleShape drawCircle(float f_radius) {
	sf::CircleShape shape(f_radius);
	return shape;
}
void shortTask(int param)
{
	int i = 0;
	while (i < param) {
		std::cout << "Processing 1" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		i++;
	}
}

void longTask()
{
	int j = 0;
	while (j < 3) {
		std::cout << "Processing 2" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		j++;
	}
}

sf::Color colour = sf::Color::Green;
sf::Vector2f v2fMove(0.0f,0.0f);

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500, 32), "Lab Week 9 - Multithreading"); //Draw an SFML window.
	sf::CircleShape shape = drawCircle(50.f); //Draw and SFML circle.
	shape.setFillColor(sf::Color::Green); //Make cicle green.


	const float f_FPS = 60.0f; //The desired FPS. (The number of updates each second).
	bool b_redraw = true;      //Do I redraw everything on the screen?

	window.setFramerateLimit(f_FPS);
	sf::Clock clock;
	shape.setOrigin(10.0f, 10.0f); //Position origin of the circle in the centre.
	shape.setPosition(150, 150.0f); //Set the intial position of the circle. 

	while (window.isOpen())
	{
		//Wait until 1/60th of a second has passed, then update everything.
		if (clock.getElapsedTime().asSeconds() >= 1.0f / f_FPS)
		{
			b_redraw = true; //We're ready to redraw everything
			shape.move(v2fMove);
			clock.restart();
		}
		//Check if the window is open or closed.
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					v2fMove = sf::Vector2f(0.0f, -1.f);
				}
				if (event.key.code == sf::Keyboard::S)
				{
					v2fMove = sf::Vector2f(0.0f, 1.f);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					v2fMove = sf::Vector2f(-1.0f, 0.f);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					v2fMove = sf::Vector2f(1.0f, 0.f);
				}

			}
		}

		//Draw to the window.
		if (b_redraw)
		{
			b_redraw = false;
			window.clear();
			shape.setFillColor(colour);
			window.draw(shape);
			window.display();
		}
	}



	return 0;
}
