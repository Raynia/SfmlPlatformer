#include "Button.h"


void Button::Initalize()
{
	this->width = this->name.getGlobalBounds().width;
	this->height = this->name.getGlobalBounds().height;
	this->left = this->name.getGlobalBounds().left;
	this->right = this->name.getGlobalBounds().left + this->name.getGlobalBounds().width;
	this->top = this->name.getGlobalBounds().top;
	this->bottom = this->name.getGlobalBounds().top + this->name.getGlobalBounds().height;
}

Button::Button()
{
	this->isMouseOver = false;
	this->nameSizeOrigin = 0U;
	this->width = 0.f, this->height = 0.f;
	this->left = 0.f, this->right = 0.f, this->top = 0.f, this->bottom = 0.f;
}

Button::Button(sf::String sfmlString, sf::Font& font, unsigned int nameSize, sf::Color color)
{
	this->isMouseOver = false;
	this->name = sf::Text(sfmlString, font, nameSize);
	this->nameSizeOrigin = nameSize;
	this->name.setFillColor(color);
	this->Initalize();
}

Button::~Button()
{
	
}

sf::Color Button::getColor()
{
	return this->name.getFillColor();
}

sf::String Button::getName()
{
	return this->name.getString();
}

sf::Font Button::getFont()
{
	return *this->name.getFont();
}

unsigned int Button::getNameSize()
{
	return this->name.getCharacterSize();
}

sf::Vector2f Button::getPosition()
{
	return this->name.getPosition();
}

sf::Vector2f Button::getScale()
{
	return this->name.getScale();
}

float Button::getRotation()
{
	return this->name.getRotation();
}

void Button::setColor(sf::Color color)
{
	this->name.setFillColor(color);
}

void Button::setName(sf::String string)
{
	this->name.setString(string);
	this->Initalize();
}

void Button::setFont(sf::Font& font)
{
	this->name.setFont(font);
	this->Initalize();
}

void Button::setNameSize(unsigned int nameSize)
{
	this->name.setCharacterSize(nameSize);
	this->Initalize();
}

void Button::setStyle(sf::Text::Style fontStyle)
{
	this->name.setStyle(fontStyle);
	this->Initalize();
}

void Button::setPosition(sf::Vector2f position)
{
	this->name.setPosition(position);
	this->Initalize();
}

void Button::setScale(sf::Vector2f scale)
{
	this->name.setScale(scale);
	this->Initalize();
}

void Button::setRotation(float rotation)
{
	this->name.setRotation(rotation);
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
	this->setNameSize(static_cast<unsigned int>(nameSizeOrigin * (window.getSize().x / 1920.f)));
	this->Initalize();
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(this->name);
}


