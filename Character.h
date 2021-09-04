#pragma once
#include "UObject.h"

class Character : public UObject
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
	void Update(sf::RenderWindow &window) override;
	void Draw(sf::RenderWindow &window) override;
};

