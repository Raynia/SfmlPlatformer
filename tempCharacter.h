#pragma once
#include <SFML/Graphics.hpp>

class tempCharacter : public sf::RectangleShape
{
private:
	int life; // 생명력
	int stamina; // 스태미너

	float speed = 150.f; //속력

public:
	enum Direction
	{
		positive = 1,
		negative = -1
	};
	
	tempCharacter();
	tempCharacter(const sf::Vector2f size);
	tempCharacter(const sf::Vector2f size, const sf::Color color);
	~tempCharacter();

	void Move(const float deltatime, const int direction);
	void Jump();
	void Update(sf::RenderWindow& window);
};

