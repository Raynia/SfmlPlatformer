#pragma once
#include "UObject.h"

class Button : public UObject
{	
private:
	sf::Text name; 
	bool isMouseOver; //mouseOver, mouseLeave시 연속 동작 방지를 위한 스위치
	unsigned int nameSizeOrigin;

	void Initalize();

public:
	float width, height;
	float left, right, top, bottom;
	sf::Vector2f position;

	Button();
	Button(sf::String string, sf::Font& font, unsigned int nameSize, sf::Color color);

	~Button();

	sf::Color getColor();
	sf::String getName();
	sf::Font getFont();
	unsigned int getNameSize();
	sf::Vector2f getPosition();
	sf::Vector2f getScale();
	float getRotation();

	void setColor(sf::Color color);
	void setName(sf::String string);
	void setFont(sf::Font& font);
	void setNameSize(unsigned int nameSize);
	void setStyle(sf::Text::Style fontStyle);
	void setPosition(sf::Vector2f position);
	void setScale(sf::Vector2f scale);
	void setRotation(float rotation);

	bool mouseClick(sf::Event event); //Button의 위치를 클릭하면 true
	bool mouseOver(sf::Event event); //Button에 마우스가 위치하면 true
	bool mouseLeave(sf::Event event); //Button에서 마우스가 떠나면 true

	void Update(sf::RenderWindow& window) override;
	void Draw(sf::RenderWindow& window) override;
};

