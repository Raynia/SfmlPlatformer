#pragma once
#include <SFML/Graphics.hpp>

class tempCharacter
{
private:
	sf::Vector2f position;
	sf::Vector2f size;

public:
	sf::RectangleShape shape;

	tempCharacter();
	~tempCharacter();

	void Move(int keycode, float deltatime);
	void Jump();
	void Update(sf::RenderWindow& window);
};

