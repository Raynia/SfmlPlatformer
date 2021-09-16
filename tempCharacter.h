#pragma once
#include <SFML/Graphics.hpp>

class tempCharacter : public sf::RectangleShape
{
private:
	int life; // 생명력
	int stamina; // 스태미너

	float movementSpeed = 200.f; //이동속도 상수

public:
	sf::Vector2f velocity;

	enum Direction
	{
		positive = 1,
		negative = -1
	};
	
	tempCharacter();
	tempCharacter(const sf::Vector2f size);
	tempCharacter(const sf::Vector2f size, const sf::Color color);
	~tempCharacter();

	void move(const float deltatime, const int direction); // 좌우 이동
	void jump(); // 점프
	void tempJump(const float deltatime, const int direction); //상하 이동 (콜리전 테스트용)
	void updateScale(sf::RenderWindow& window);
};

