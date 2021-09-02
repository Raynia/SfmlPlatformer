#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Button
{
	sf::Text text;
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f position;
	sf::Vector2f size;
	
	void onClick();
	void Draw();
	void Rescale();
};

