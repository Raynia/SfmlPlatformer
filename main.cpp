﻿#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <vector>

#define GRAPHIC_RESOURCE "resource/graphics/"
#define MUSIC_RESOURCE "resource/music/"
#define FONTS_RESOURCE "resource/fonts/"

int main()
{
	///////////////////////////////////////////
	//
	// 어플리케이션 윈도우 속성값
	//
	///////////////////////////////////////////
	std::srand(static_cast<unsigned int>(std::time(NULL)));	

	std::vector<sf::VideoMode> videoMode = sf::VideoMode::getFullscreenModes();

	sf::Uint32 windowWidth = 1280U; //set screen width
	sf::Uint32 windowHeight = 720U; //set screen height
	sf::String windowTitle(std::string("Platformer")); //set title

	sf::ContextSettings windowContextAttr;
	windowContextAttr.depthBits = 32U;
	windowContextAttr.stencilBits = 8U;
	windowContextAttr.antialiasingLevel = 8U;
	windowContextAttr.majorVersion = 4U;
	windowContextAttr.minorVersion = 0U;

	const int32_t windowFullScreen = sf::Style::Close | sf::Style::Fullscreen;
	const int32_t windowWindowScreen = sf::Style::Close;
		
	sf::Font fontEnglish;
	sf::Font fontEastAsia;
	if (!fontEnglish.loadFromFile(FONTS_RESOURCE"Dynastium-Kjvy.ttf") ||
		!fontEastAsia.loadFromFile("c:/windows/fonts/gulim.ttc"))
		return EXIT_FAILURE;

	///////////////////////////////////////////
	//
	// 어플리케이션 윈도우 최초 생성
	//
	///////////////////////////////////////////

	sf::RenderWindow window;
	window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, windowWindowScreen, windowContextAttr);

	///////////////////////////////////////////
	//
	// 기능 사용을 위한 스위치
	//
	///////////////////////////////////////////

	bool isFullscreen = false; // 전체화면 여부를 확인
	bool isWindowCreate = true; // 윈도우 (재)생성 여부를 확인
	bool isSceneSwitch = true; // Scene 변경 여부를 확인
	bool isLoading = true;

	///////////////////////////////////////////
	//
	// 오브젝트 상수
	//
	///////////////////////////////////////////

	const sf::Color BLACK(0U, 0U, 0U);
	const sf::Color WHITE(255U, 255U, 255U);
	const sf::Color RED(255U, 0U, 0U);

	///////////////////////////////////////////
	//
	// 오브젝트 변수
	//
	///////////////////////////////////////////

	/* 그래픽 오브젝트 (Texture -> Sprite - > Font) */

	sf::Texture textureTitleBG; //타이틀 화면 배경 텍스쳐
	sf::Texture texture2;

	if (!textureTitleBG.loadFromFile(GRAPHIC_RESOURCE"background_test.jpg") ||
		!texture2.loadFromFile(GRAPHIC_RESOURCE"logo_1.jpg"))
		return EXIT_FAILURE;

	textureTitleBG.setSmooth(true);
	texture2.setSmooth(true);

	sf::Sprite spriteTitleBG; //타이틀 화면 배경 스프라이트
	sf::Sprite sprite2;

	spriteTitleBG.setTexture(textureTitleBG);
	sprite2.setTexture(texture2);

	sf::Text buttonTitleNewGame(L"New Game", fontEnglish, 50U);
	sf::Text buttonTitleContinue(L"Continue", fontEnglish);
	sf::Text buttonTitleOptions(L"Options", fontEnglish);
	sf::Text buttonTitleExit(L"Exit", fontEnglish);

	buttonTitleNewGame.setFillColor(BLACK);
	buttonTitleContinue.setFillColor(BLACK);
	buttonTitleOptions.setFillColor(BLACK);
	buttonTitleExit.setFillColor(BLACK);

	float titleButtonDistance = 100.f;
	unsigned int titleButtonY = 0U;
	const unsigned int titleButtonCharacterSize = 45U;

	/*
	사운드 오브젝트 
	- 배경음 등 파일 크기가 큰 오브젝트는 필요한 Scene에서 sf::Music으로 로딩
	- 파일 크기가 작은 오브젝트는 sf::SoundBuffer에 저장 후 sf::Sound에 로딩	
	*/

	sf::SoundBuffer soundeffectClick;
	sf::SoundBuffer soundeffectDecide;
	sf::Music backgroundmusic;
	sf::Sound soundeffect;

	if (!soundeffectClick.loadFromFile(MUSIC_RESOURCE"click.wav") ||
		!soundeffectDecide.loadFromFile(MUSIC_RESOURCE"confirm.wav"))
		return EXIT_FAILURE;

	backgroundmusic.setVolume(50.f);
	soundeffect.setVolume(50.f);

	/*sf::Vector2u titleUISize(100u, 40u);
	sf::Vector2u titleUIPosition(910u, 500u);
	sf::Rect<unsigned int> rect(titleUIPosition, titleUISize);*/
	
	///////////////////////////////////////////
	//
	// 세부 구현을 위한 변수 및 함수
	// 
	///////////////////////////////////////////

	sf::Clock clock;

	///////////////////////////////////////////
	//
	// 
	// 기능 테스트 혹은 개발용 변수 및 함수
	//
	// 
	///////////////////////////////////////////

	bool testScene1 = true;
	bool testScene2 = false;

	bool testTitleOptionSwitch = false;
	bool testTitleStartSwitch = false;
	bool testTitleHideSwitch = false;

	int testCount = 0;
	sf::Clock testClock;

	sf::Text testTextOptions, testTextMenuButton;
	testTextOptions.setFont(fontEnglish);
	testTextOptions.setString(L"Insted of Options");
	
	sf::Sprite testSpriteforView;
	testSpriteforView.setTexture(texture2);

	sf::Text debugAlphaVersionInfo(L"This game is now currently development", fontEnglish);
	debugAlphaVersionInfo.setFillColor(sf::Color(255U, 0U, 0U));

	float testMenuButtonPositionY = 0.f;	

	sf::Rect<float> testRect;
	testRect = sf::FloatRect();

	//윈도우 루프 시작

	while (window.isOpen())
	{
		sf::Event event;
		
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			//창 모드에서 닫기 버튼 클릭 시 이벤트

			case sf::Event::Closed:
				window.close();
				break;

			//키보드 입력 시 이벤트

			case sf::Event::KeyPressed:

				//윈도우 재생성 기능 테스트
				//전체화면과 윈도우화면 간의 전환 시 윈도우 자체를 재생성
				//isFullscreen과 isWindowCreate를 true로 변경

				if (event.key.code == sf::Keyboard::S && !isFullscreen)
				{
					window.create(sf::VideoMode::getDesktopMode(), windowTitle, windowFullScreen, windowContextAttr);
					isFullscreen = true;
					isWindowCreate = true;
				}
				else if (event.key.code == sf::Keyboard::S && isFullscreen)
				{
					window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, windowWindowScreen, windowContextAttr);
					isFullscreen = false;
					isWindowCreate = true;
				}

				if (event.key.code == sf::Keyboard::D)
				{
					if (!testScene1 && testScene2)
					{
						testScene1 = true;
						testScene2 = false;
						isSceneSwitch = true;
					}
				}

				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}

				break;
			
			// 마우스 클릭 시 이벤트
			// Button 클래스와 같이 모듈화를 통해 코드 간략화 필요

			case sf::Event::MouseButtonPressed:
				if (testScene1)
				{
					if (event.mouseButton.x >= buttonTitleNewGame.getGlobalBounds().left &&
						event.mouseButton.x <= buttonTitleNewGame.getGlobalBounds().left + buttonTitleNewGame.getGlobalBounds().width &&
						event.mouseButton.y >= buttonTitleNewGame.getGlobalBounds().top &&
						event.mouseButton.y <= buttonTitleNewGame.getGlobalBounds().top + buttonTitleNewGame.getGlobalBounds().height)
					{						
						testScene1 = false;
						testScene2 = true;
						
						isSceneSwitch = true;
					}

					if (event.mouseButton.x >= buttonTitleContinue.getGlobalBounds().left &&
						event.mouseButton.x <= buttonTitleContinue.getGlobalBounds().left + buttonTitleContinue.getGlobalBounds().width &&
						event.mouseButton.y >= buttonTitleContinue.getGlobalBounds().top &&
						event.mouseButton.y <= buttonTitleContinue.getGlobalBounds().top + buttonTitleContinue.getGlobalBounds().height)
					{

						std::cout << "Continue button pressed\n";
						soundeffect.setBuffer(soundeffectDecide);
						soundeffect.play();
					}

					if (event.mouseButton.x >= buttonTitleOptions.getGlobalBounds().left &&
						event.mouseButton.x <= buttonTitleOptions.getGlobalBounds().left + buttonTitleOptions.getGlobalBounds().width &&
						event.mouseButton.y >= buttonTitleOptions.getGlobalBounds().top &&
						event.mouseButton.y <= buttonTitleOptions.getGlobalBounds().top + buttonTitleOptions.getGlobalBounds().height)
					{
						std::cout << "Options button pressed\n";
						soundeffect.setBuffer(soundeffectDecide);
						soundeffect.play();
					}

					if (event.mouseButton.x >= buttonTitleExit.getGlobalBounds().left &&
						event.mouseButton.x <= buttonTitleExit.getGlobalBounds().left + buttonTitleExit.getGlobalBounds().width &&
						event.mouseButton.y >= buttonTitleExit.getGlobalBounds().top &&
						event.mouseButton.y <= buttonTitleExit.getGlobalBounds().top + buttonTitleExit.getGlobalBounds().height)
						window.close();
					
				}
				break;
			
			default:
				break;
			}
				
			
			
		}
		
		// 윈도우 (재)생성 시 실행되는 기능
		// isWindowCreate 스위치로 온오프
		// 실행 시 윈도우 사이즈에 맞게 sprite와 view의 크기를 재조정
		// 완료 후 isWindowCreate는 false로 변경됨

		if (isWindowCreate)
		{
			//Sprite 정보 변경

			spriteTitleBG.setScale(sf::Vector2f(window.getSize().x / spriteTitleBG.getLocalBounds().width,
				window.getSize().y / spriteTitleBG.getLocalBounds().height));
			sprite2.setScale(sf::Vector2f(window.getSize().x / sprite2.getLocalBounds().width,
				window.getSize().y / spriteTitleBG.getLocalBounds().height));
						
			//Text 정보 변경

			titleButtonDistance = 120.f * (window.getSize().x / 1920.f);
			titleButtonY = static_cast<unsigned int> (window.getSize().y * (3.f / 4.f));

			debugAlphaVersionInfo.setCharacterSize(static_cast<unsigned int>(30 * (window.getSize().x / 1920.f)));

			buttonTitleNewGame.setCharacterSize(titleButtonCharacterSize * (window.getSize().x / 1920.f));
			buttonTitleContinue.setCharacterSize(titleButtonCharacterSize * (window.getSize().x / 1920.f));
			buttonTitleOptions.setCharacterSize(titleButtonCharacterSize * (window.getSize().x / 1920.f));
			buttonTitleExit.setCharacterSize(titleButtonCharacterSize * (window.getSize().x / 1920.f));

			
			buttonTitleContinue.setPosition(
				window.getSize().x / 2 - buttonTitleContinue.getGlobalBounds().width,
				titleButtonY);
			buttonTitleNewGame.setPosition(
				buttonTitleContinue.getGlobalBounds().left - (titleButtonDistance + buttonTitleNewGame.getGlobalBounds().width),
				titleButtonY);
			buttonTitleOptions.setPosition(
				buttonTitleContinue.getGlobalBounds().width + buttonTitleContinue.getGlobalBounds().left + titleButtonDistance,
				titleButtonY);
			buttonTitleExit.setPosition(
				buttonTitleOptions.getGlobalBounds().width + buttonTitleOptions.getGlobalBounds().left + titleButtonDistance,
				titleButtonY);

			//View 사이즈 변경

			sf::FloatRect visibleArea(0.f, 0.f, window.getSize().x, window.getSize().y);
			window.setView(sf::View(visibleArea));

			isWindowCreate = false;
		}

		//
		
		float deltatime = clock.restart().asSeconds();

		//오브젝트가 윈도우에 그려지는 구간

		window.clear();

		if (testScene1)
		{			
			window.draw(spriteTitleBG);

			if (isSceneSwitch)
			{
				backgroundmusic.stop();
				backgroundmusic.openFromFile(MUSIC_RESOURCE"title.ogg");
				backgroundmusic.play();
				isSceneSwitch = false;
			}
			
			window.draw(buttonTitleNewGame);
			window.draw(buttonTitleContinue);
			window.draw(buttonTitleOptions);
			window.draw(buttonTitleExit);

			if (testTitleOptionSwitch)
				window.draw(testTextOptions);
		}

		if (testScene2)
		{
			window.draw(sprite2);

			if (isSceneSwitch)
			{
				backgroundmusic.stop();
				backgroundmusic.openFromFile(MUSIC_RESOURCE"test.ogg");
				backgroundmusic.play();
				isSceneSwitch = false;
			}
		}

		window.draw(debugAlphaVersionInfo);
		window.display();
	}

	return EXIT_SUCCESS;
}