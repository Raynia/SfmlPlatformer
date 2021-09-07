#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Character
{
private:
	sf::Vector2f position;
	sf::Vector2f size;

	std::vector<sf::Sprite> spriteIdle;
	std::vector<sf::Sprite> spriteMove;
	std::vector<sf::Sprite> spriteJump;

public:
	sf::RectangleShape shape;

	Character();
	~Character();

	void Idle();
	void Move(int keycode, float deltatime);
	void Jump();
	void Update(sf::RenderWindow &window);
};

