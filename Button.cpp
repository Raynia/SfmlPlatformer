#include "Button.h"


void Button::Initalize()
{
	this->width = this->getGlobalBounds().width;
	this->height = this->getGlobalBounds().height;
	this->left = this->getGlobalBounds().left;
	this->right = this->getGlobalBounds().left + this->getGlobalBounds().width;
	this->top = this->getGlobalBounds().top;
	this->bottom = this->getGlobalBounds().top + this->getGlobalBounds().height;
}

Button::Button()
{
	this->isMouseOver = false;
	this->nameSizeOrigin = 0U;
	this->width = 0.f, this->height = 0.f;
	this->left = 0.f, this->right = 0.f, this->top = 0.f, this->bottom = 0.f;
}

Button::Button(sf::String string, sf::Font& font, unsigned int characterSize, sf::Color color)
{
	this->isMouseOver = false;

	this->setString(string);
	this->setFont(font);
	this->setCharacterSize(characterSize);
	this->nameSizeOrigin = characterSize;
	this->setFillColor(color);

	this->Initalize();
}

Button::~Button()
{

}

void Button::setPosition(sf::Vector2f position)
{
	this->Text::setPosition(position);
	this->Initalize();
}

void Button::setPosition(float x, float y)
{
	this->Text::setPosition(x, y);
	this->Initalize();
}

bool Button::mouseClick(sf::Event event)
{
	if (event.mouseButton.x >= this->left && event.mouseButton.x <= this->right &&
		event.mouseButton.y >= this->top &&	event.mouseButton.y <= this->bottom)
		return true;

	else
		return false;
}

bool Button::mouseOver(sf::Event event)
{
	return true;
}

bool Button::mouseLeave(sf::Event event)
{
	return true;
}

void Button::Update(sf::RenderWindow& window)
{	
	this->setCharacterSize(static_cast<unsigned int>(nameSizeOrigin * (window.getSize().x / 1920.f)));
	this->Initalize();
}


