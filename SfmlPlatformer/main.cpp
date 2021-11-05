#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <vector>

#include "tempCharacter.h"
#include "Button.h"

#define GRAPHIC_RESOURCE "resource/graphics/"
#define MUSIC_RESOURCE "resource/music/"
#define FONTS_RESOURCE "resource/fonts/"

#define MAX_WINDOW_WIDTH 1920.f
#define MAX_WINDOW_HEIGHT 1080.f

// 색상 상수

const sf::Color BLACK(0U, 0U, 0U);
const sf::Color WHITE(255U, 255U, 255U);
const sf::Color RED(255U, 0U, 0U);
const sf::Color BLUE(0U, 0U, 255U);
const sf::Color GREEN(0U, 255U, 0U);

float scale(float targetSize, float windowScaleRatio)
{
	return (targetSize * windowScaleRatio);
}

int main()
{
	///////////////////////////////////////////
	//
	// 윈도우 초기화 및 생성
	//
	///////////////////////////////////////////

	// 윈도우 속성 변수 및 상수

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

	// 윈도우 최초 생성

	sf::RenderWindow window;
	window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, windowWindowScreen, windowContextAttr);

	///////////////////////////////////////////
	//
	// 스위치
	//
	///////////////////////////////////////////

	bool isFullscreen = false; // 전체화면 여부를 확인
	bool isWindowCreate = true; // 윈도우 (재)생성 여부를 확인
	bool isSceneSwitch = true; // Scene 변경 여부를 확인
	bool isLoading = true;

	bool isTitleScene = true;
	bool isTestStage = false;

	///////////////////////////////////////////
	//
	// Scene
	// 
	// 사운드 오브젝트 유의사항
	//- 배경음 등 파일 크기가 큰 오브젝트는 필요한 Scene에서 sf::Music으로 로딩
	// -파일 크기가 작은 오브젝트는 sf::SoundBuffer에 저장 후 sf::Sound에 로딩
	// 
	///////////////////////////////////////////

	// 글로벌

	sf::SoundBuffer soundeffectClick;
	sf::SoundBuffer soundeffectDecide;
	sf::Music backgroundmusic;
	sf::Sound soundeffect;

	if (!soundeffectClick.loadFromFile(MUSIC_RESOURCE"click.wav") ||
		!soundeffectDecide.loadFromFile(MUSIC_RESOURCE"confirm.wav"))
		return EXIT_FAILURE;

	backgroundmusic.setVolume(50.f);
	soundeffect.setVolume(50.f);

	// Title scene

	sf::View titleView(sf::FloatRect(0.f, 0.f, static_cast<float>(MAX_WINDOW_WIDTH), static_cast<float>(MAX_WINDOW_HEIGHT)));

	sf::Texture textureTitleBG; //타이틀 화면 배경 텍스쳐

	if (!textureTitleBG.loadFromFile(GRAPHIC_RESOURCE"background_temp.jpg"))
		return EXIT_FAILURE;

	textureTitleBG.setSmooth(true);

	sf::Sprite spriteTitleBG; //타이틀 화면 배경 스프라이트

	spriteTitleBG.setTexture(textureTitleBG);

	Button buttonTitleNewGame(L"New Game", fontEnglish, 50U, BLACK);
	Button buttonTitleContinue(L"Continue", fontEnglish, 50U, BLACK);
	Button buttonTitleOptions(L"Options", fontEnglish, 50U, BLACK);
	Button buttonTitleExit(L"Exit", fontEnglish, 50U, BLACK);

	float titleButtonDistance = 100.f;
	unsigned int titleButtonY = 0U;
	const unsigned int titleButtonCharacterSize = 45U;

	//test stage scene	

	sf::View inGameView(sf::FloatRect(0.f, 0.f, static_cast<float>(MAX_WINDOW_WIDTH), static_cast<float>(MAX_WINDOW_HEIGHT)));

	float floorY = 100.f;
	float floatingPlatformY = 50.f;

	sf::RectangleShape testFloor1(sf::Vector2f(2000.f, floorY));
	sf::RectangleShape testFloor2(sf::Vector2f(500.f, floorY));
	sf::RectangleShape testFloor4(sf::Vector2f(1000.f, floorY));
	testFloor1.setFillColor(WHITE);
	testFloor2.setFillColor(GREEN);
	testFloor4.setFillColor(GREEN);
	sf::RectangleShape testFloor3(testFloor2);

	sf::RectangleShape testFloatingPlatform1(sf::Vector2f(250.f, floatingPlatformY));
	testFloatingPlatform1.setFillColor(BLUE);
	sf::RectangleShape testFloatingPlatform2(testFloatingPlatform1);
	sf::RectangleShape testFloatingPlatform3(testFloatingPlatform1);

	std::vector<sf::RectangleShape*> floorsTestStage;
	floorsTestStage.push_back(&testFloor1);
	floorsTestStage.push_back(&testFloor2);
	floorsTestStage.push_back(&testFloor3);
	floorsTestStage.push_back(&testFloor4);

	std::vector<sf::RectangleShape*> floatingPlatformsTestStage;
	floatingPlatformsTestStage.push_back(&testFloatingPlatform1);
	floatingPlatformsTestStage.push_back(&testFloatingPlatform2);
	floatingPlatformsTestStage.push_back(&testFloatingPlatform3);

	//std::vector<std::vector<sf::RectangleShape*>> collisionTestStagePlatforms;

	///////////////////////////////////////////
	// 
	// 캐릭터
	//  
	///////////////////////////////////////////

	tempCharacter tempChara(sf::Vector2f(50.f, 140.f), RED);
	
	///////////////////////////////////////////
	//
	// 기능 변수 및 함수
	// 
	///////////////////////////////////////////
	
	sf::Clock clock;

	///////////////////////////////////////////
	// 
	// 기능 테스트 혹은 개발용 변수 및 함수
	// 
	///////////////////////////////////////////

	sf::Text debugAlphaVersionInfo(L"This game is now currently development", fontEnglish);
	debugAlphaVersionInfo.setFillColor(sf::Color(255U, 0U, 0U));

	sf::FloatRect nextPos;

	///////////////////////////////////////////
	// 
	// 윈도우 루프 시작
	// 
	///////////////////////////////////////////

	while (window.isOpen())
	{
		sf::Event event;

		///////////////////////////////////////////
		// 
		// SFML 이벤트
		//
		///////////////////////////////////////////	

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
					if (!isTitleScene && isTestStage)
					{
						isTitleScene = true;
						isTestStage = false;
						isSceneSwitch = true;
					}
				}

				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					tempChara.jump();
				}

				if (event.key.code == sf::Keyboard::P)
				{
					std::cout << "-------------------\n";
				}

				break;
			
			// 마우스 클릭 시 이벤트
			// Button 클래스와 같이 모듈화를 통해 코드 간략화 필요

			case sf::Event::MouseButtonPressed:
				if (isTitleScene)
				{
					if (buttonTitleNewGame.mouseClick(event))
					{
						isTitleScene = false;
						isTestStage = true;
						isSceneSwitch = true;
					}					

					if (buttonTitleContinue.mouseClick(event))
					{
						std::cout << "Continue button pressed\n";
						soundeffect.setBuffer(soundeffectDecide);
						soundeffect.play();
					}

					if (buttonTitleOptions.mouseClick(event))
					{
						std::cout << "Options button pressed\n";
						soundeffect.setBuffer(soundeffectDecide);
						soundeffect.play();
					}

					if (buttonTitleExit.mouseClick(event))
						window.close();					
				}
				break;
			
			default:
				break;
			}			
		}

		///////////////////////////////////////////
		// 
		// 키보드 / 마우스 이벤트 - deltatime
		//
		///////////////////////////////////////////	

		float deltatime = clock.restart().asSeconds();

		if (isTestStage)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				tempChara.move(deltatime, tempCharacter::Direction::negative);
				
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				tempChara.move(deltatime, tempCharacter::Direction::positive);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				tempChara.tempJump(deltatime, tempCharacter::Direction::negative);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{ 
				tempChara.tempJump(deltatime, tempCharacter::Direction::positive);
			}

		}
		
		///////////////////////////////////////////	
		// 
		// 윈도우 (재)생성 이벤트
		// isWindowCreate 스위치로 온오프
		// 실행 시 윈도우 사이즈에 맞게 sprite와 view의 크기를 재조정
		// 완료 후 isWindowCreate는 false로 변경됨
		// 
		///////////////////////////////////////////	

		if (isWindowCreate)
		{
			//오브젝트 정보 변경
			float windowScaledX = window.getSize().x / MAX_WINDOW_WIDTH;
			float windowScaledY = window.getSize().y / MAX_WINDOW_HEIGHT;

			unsigned int windowChangedSizeX = window.getSize().x;
			unsigned int windowChangedSizeY = window.getSize().y;

			spriteTitleBG.setScale(sf::Vector2f(windowChangedSizeX / spriteTitleBG.getLocalBounds().width,
				windowChangedSizeY / spriteTitleBG.getLocalBounds().height));

			testFloor1.setScale(sf::Vector2f(windowScaledX, windowScaledY));
			testFloor2.setScale(sf::Vector2f(windowScaledX, windowScaledY));
			testFloor3.setScale(sf::Vector2f(windowScaledX, windowScaledY));
			testFloor4.setScale(sf::Vector2f(windowScaledX, windowScaledY));

			testFloor1.setPosition(
				sf::Vector2f(0.f, windowChangedSizeY - testFloor1.getGlobalBounds().height));
			testFloor2.setPosition(
				sf::Vector2f(testFloor1.getGlobalBounds().left + testFloor1.getGlobalBounds().width + scale(200.f, windowScaledX),
					testFloor1.getPosition().y));
			testFloor3.setPosition(
				sf::Vector2f(testFloor2.getGlobalBounds().left + testFloor2.getGlobalBounds().width + scale(250.f, windowScaledX),
					testFloor2.getPosition().y));

			testFloatingPlatform1.setPosition(
				sf::Vector2f(testFloor3.getGlobalBounds().left + testFloor3.getGlobalBounds().width + scale(200.f, windowScaledX),
					testFloor3.getPosition().y - testFloatingPlatform1.getGlobalBounds().height));
			testFloatingPlatform2.setPosition(
				sf::Vector2f(testFloatingPlatform1.getGlobalBounds().left + testFloatingPlatform1.getGlobalBounds().width + scale(200.f, windowScaledX),
					testFloatingPlatform1.getPosition().y));
			testFloatingPlatform3.setPosition(
				sf::Vector2f(testFloatingPlatform2.getGlobalBounds().left + testFloatingPlatform2.getGlobalBounds().width + scale(200.f, windowScaledX),
					testFloatingPlatform2.getPosition().y));

			testFloor4.setPosition(
				sf::Vector2f(testFloatingPlatform3.getGlobalBounds().left + testFloatingPlatform3.getGlobalBounds().width + scale(250.f, windowScaledX),
					testFloor3.getPosition().y));

			tempChara.updateScale(window);
			tempChara.setPosition(sf::Vector2f(0.f, 0.f));

			//UI 정보 변경

			titleButtonDistance = scale(120.f, windowScaledX);
			titleButtonY = static_cast<unsigned int>(windowChangedSizeY * (3.f / 4.f));

			buttonTitleNewGame.updateScale(window);
			buttonTitleContinue.updateScale(window);
			buttonTitleOptions.updateScale(window);
			buttonTitleExit.updateScale(window);

			buttonTitleContinue.setPosition(
				sf::Vector2f(windowChangedSizeX / 2 - buttonTitleContinue.width,
					static_cast<float>(titleButtonY)));

			buttonTitleNewGame.setPosition(
				sf::Vector2f(buttonTitleContinue.left - (titleButtonDistance + buttonTitleNewGame.width),
					static_cast<float>(titleButtonY)));

			buttonTitleOptions.setPosition(
				sf::Vector2f(buttonTitleContinue.right + titleButtonDistance,
					static_cast<float>(titleButtonY)));

			buttonTitleExit.setPosition(
				sf::Vector2f(buttonTitleOptions.right + titleButtonDistance,
					static_cast<float>(titleButtonY)));

			debugAlphaVersionInfo.setCharacterSize(static_cast<unsigned int>(30 * windowScaledX));
	

			//View 정보 변경
			
			titleView.setSize(static_cast<float>(windowChangedSizeX), static_cast<float>(windowChangedSizeY));
			titleView.setCenter(titleView.getSize().x / 2.f, titleView.getSize().y / 2.f);

			inGameView.setSize(static_cast<float>(windowChangedSizeX), static_cast<float>(windowChangedSizeY));			
			inGameView.setCenter(inGameView.getSize().x / 2.f, inGameView.getSize().y / 2.f);

			isWindowCreate = false;
		}

		///////////////////////////////////////////
		// 
		// 콜리전 처리 (스테이지 전용)
		// 
		// 스크린 -> 플로어 -> 오브젝트 순서로 적용
		// 
		// 오브젝트 콜리전 처리는 해당 오브젝트의 콜리전 규칙에 따라 처리
		// 
		// 플로어는 다음 순서로 처리
		// 1. 상단 충돌 -> 캐릭터가 플로어 위에 있음
		// 2. 하단 충돌 -> 캐릭터가 점프 중 플로어와 접촉
		// 3. 측면 충돌 -> 캐릭터가 플로어에서 이탈하여 낙하 중
		// 4. 충돌하지 않음 -> 캐릭터가 플로어에서 이탈
		//
		///////////////////////////////////////////

		if (isTestStage)
		{
			for (auto floor : floorsTestStage)
			{
				sf::FloatRect playerBounds = tempChara.getGlobalBounds();
				sf::FloatRect floorBounds = floor->getGlobalBounds();

				nextPos = playerBounds;
				nextPos.left += tempChara.velocity.x;
				nextPos.top += tempChara.velocity.y;
				
				if (floorBounds.intersects(nextPos))
				{
					if (floorBounds.top <= nextPos.top + nextPos.height)
					{
						tempChara.setPosition(playerBounds.left, floorBounds.top - playerBounds.height);
					}

				}
			}

			for (auto platform : floatingPlatformsTestStage)
			{
				sf::FloatRect playerBounds = tempChara.getGlobalBounds();
				sf::FloatRect platFormBounds = platform->getGlobalBounds();

				nextPos = playerBounds;
				nextPos.left += tempChara.velocity.x;
				nextPos.top += tempChara.velocity.y;

				if (platFormBounds.intersects(nextPos))
				{

				}
			}
		}		

		///////////////////////////////////////////
		// 
		// 윈도우에 오브젝트 출력
		//
		///////////////////////////////////////////

		window.clear();

		//타이틀
		if (isTitleScene)
		{			

			window.draw(spriteTitleBG);

			if (isSceneSwitch)
			{
				backgroundmusic.stop();
				backgroundmusic.openFromFile(MUSIC_RESOURCE"title.ogg");
				backgroundmusic.play();
				
				
				window.setView(titleView);
				isSceneSwitch = false;
			}
			
			window.draw(buttonTitleNewGame);
			window.draw(buttonTitleContinue);
			window.draw(buttonTitleOptions);
			window.draw(buttonTitleExit);
		}

		//테스트 스테이지
		if (isTestStage)
		{
			if (isSceneSwitch)
			{
				backgroundmusic.stop();
				backgroundmusic.openFromFile(MUSIC_RESOURCE"test.ogg");
				backgroundmusic.play();
				isSceneSwitch = false;
			}

			window.draw(tempChara);
			window.draw(testFloor1);
			window.draw(testFloor2);
			window.draw(testFloor3);
			window.draw(testFloatingPlatform1);
			window.draw(testFloatingPlatform2);
			window.draw(testFloatingPlatform3);
			window.draw(testFloor4);

			if (tempChara.getPosition().x >= inGameView.getSize().x / 2.f)
			{
				inGameView.setCenter(tempChara.getPosition().x, inGameView.getSize().y / 2.f); //플레이어가 조작하는 캐릭터의 위치를 실시간으로 적용
			}
			else
			{
				inGameView.setCenter(inGameView.getSize().x / 2.f, inGameView.getSize().y / 2.f);
			}
			
			window.setView(inGameView); 
		}

		//글로벌
		window.draw(debugAlphaVersionInfo);

		window.display();
	}

	return EXIT_SUCCESS;
}