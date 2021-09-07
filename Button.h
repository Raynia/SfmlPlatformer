#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Text
{	
private:
	bool isMouseOver; //mouseOver, mouseLeave시 연속 동작 방지를 위한 스위치
	unsigned int originCharacterSize;

	void Initalize();

public:
	float width, height;
	float left, right, top, bottom;
	
	Button();
	Button(sf::String string, sf::Font& font, unsigned int characterSize, sf::Color color);

	~Button();

	void setPosition(sf::Vector2f position); 
	void setPosition(float x, float y);

	bool mouseClick(sf::Event event); //Button의 위치를 클릭하면 true
	bool mouseOver(sf::Event event); //Button에 마우스가 위치하면 true
	bool mouseLeave(sf::Event event); //Button에서 마우스가 떠나면 true

	void Update(sf::RenderWindow& window);
};

