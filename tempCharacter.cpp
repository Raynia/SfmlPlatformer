#include "tempCharacter.h"

tempCharacter::tempCharacter() : life(100), stamina(100), velocity(sf::Vector2f(0.f, 0.f))
{
	this->setSize(sf::Vector2f(0.f, 0.f));
}	

tempCharacter::tempCharacter(const sf::Vector2f size) : life(100), stamina(100), velocity(sf::Vector2f(0.f, 0.f))
{
	this->setSize(size);
}

tempCharacter::tempCharacter(const sf::Vector2f size, const sf::Color color) : life(100), stamina(100), velocity(sf::Vector2f(0.f, 0.f))
{
	this->setSize(size);
	this->setFillColor(color);
}

tempCharacter::~tempCharacter()
{

}

void tempCharacter::move(const float deltatime, const int direction)
{
	//sf::Vector2f offset(this->movementSpeed * deltatime * direction, 0.f);
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->velocity.x = this->movementSpeed * deltatime * direction;

	this->RectangleShape::move(velocity);
}

void tempCharacter::jump()
{
	this->RectangleShape::move(0.f, -50.f);
}

void tempCharacter::tempJump(const float deltatime, const int direction)
{
	//sf::Vector2f offset(0.f, this->movementSpeed * deltatime * direction);
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->velocity.y = this->movementSpeed * deltatime * direction;

	this->RectangleShape::move(velocity);
}

void tempCharacter::updateScale(sf::RenderWindow& window)
{
	this->setScale(window.getSize().x / 1920.f, window.getSize().y / 1080.f);
}
