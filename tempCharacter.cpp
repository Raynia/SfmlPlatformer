#include "tempCharacter.h"

tempCharacter::tempCharacter() : life(100), stamina(100)
{
	this->setSize(sf::Vector2f(0.f, 0.f));
}	

tempCharacter::tempCharacter(const sf::Vector2f size) : life(100), stamina(100)
{
	this->setSize(size);
}

tempCharacter::tempCharacter(const sf::Vector2f size, const sf::Color color) : life(100), stamina(100)
{
	this->setSize(size);
	this->setFillColor(color);
}

tempCharacter::~tempCharacter()
{

}

void tempCharacter::move(const float deltatime, const int direction)
{
	sf::Vector2f offset(this->speed * deltatime * direction, 0.f);

	this->RectangleShape::move(offset);
}

void tempCharacter::jump()
{
	
}

void tempCharacter::updateScale(sf::RenderWindow& window)
{
	this->setScale(window.getSize().x / 1920.f, window.getSize().y / 1080.f);
}
