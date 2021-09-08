#include "Character.h"

Character::Character()
{
	shape.setSize(sf::Vector2f(50.f, 120.f));
	shape.setFillColor(sf::Color(255U, 0U, 0U));
}

Character::~Character()
{
}

void Character::Idle()
{
}

void Character::move(int keycode, float deltatime)
{
	float speed = 100.f;
	int direction = 1; //1 = positive, -1 = negative, 0 = wrong button

	if (keycode == sf::Keyboard::Right)
		direction = 1;
	else if (keycode == sf::Keyboard::Left)
		direction = -1;
	else
		direction = 0;
	 
	sf::Vector2f offset(speed * deltatime * direction , 0.f);

	this->shape.move(offset);
}

void Character::jump()
{
	sf::Vector2f offset(shape.getPosition().x, shape.getPosition().y);

	float x = this->shape.getPosition().x;
	float y = this->shape.getPosition().y;

	float velocityX = 0.f;
	float velocityY = -10.f;
	float accelerationX = 0.f;
	float accelerationY = 0.f;
	float gravity = 2.f;

	velocityY += accelerationY;

	y += velocityY;

	offset.y = y;
	
	this->shape.setPosition(offset);
}

void Character::updateScale(sf::RenderWindow& window)
{
	sf::Vector2f standardSize(1920.f, 1080.f);
	this->shape.setScale(window.getSize().x / standardSize.x, window.getSize().y / standardSize.y);
}
