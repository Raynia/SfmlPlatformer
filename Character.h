#pragma once
#include <SFML/Graphics.hpp>

class Character
{
private:
	sf::Vector2f position;
	sf::Vector2f size;

public:
	sf::RectangleShape shape;

	Character();
	~Character();

	void Move(int keycode, float deltatime);
	void Jump();
	void Update(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
};

