#include "tempCharacter.h"

tempCharacter::tempCharacter()
{

}

tempCharacter::~tempCharacter()
{

}

void tempCharacter::Move(int keycode, float deltatime)
{
	float speed = 100.f;
	int direction = 1; //1 = positive, -1 = negative, 0 = wrong button

	if (keycode == sf::Keyboard::Right)
		direction = 1;
	else if (keycode == sf::Keyboard::Left)
		direction = -1;
	else
		direction = 0;

	sf::Vector2f offset(speed * deltatime * direction, 0.f);
}

void tempCharacter::Jump()
{

}

void tempCharacter::Update(sf::RenderWindow& window)
{
	this->shape.setScale(window.getSize().x / 1920.f, window.getSize().y / 1080.f);
}
