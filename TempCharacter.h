#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class TempCharacter
{
private:
	sf::Vector2f position;
	sf::Vector2f size;

public:
	sf::RectangleShape shape;

	TempCharacter();

	void Move(int keycode, float deltatime);
	void Jump();
	void Rescale(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
};

