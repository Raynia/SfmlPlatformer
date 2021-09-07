#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <vector>

#include "Character.h"
#include "Button.h"

#define GRAPHIC_RESOURCE "resource/graphics/"
#define MUSIC_RESOURCE "resource/music/"
#define FONTS_RESOURCE "resource/fonts/"

int main()
{
	///////////////////////////////////////////
	//
	// 윈도우 초기화 및 생성
	//
	///////////////////////////////////////////

	// 윈도우 속성값

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
	// 상수
	//
	///////////////////////////////////////////

	const sf::Color BLACK(0U, 0U, 0U);
	const sf::Color WHITE(255U, 255U, 255U);
	const sf::Color RED(255U, 0U, 0U);

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
	sf::RectangleShape tempFloor1, tempFloor2, tempFloor3, tempFloor4;
	sf::RectangleShape tempFloatingPlatform1, tempFloatingPlatform2;

	///////////////////////////////////////////
	// 
	// 캐릭터
	//  
	///////////////////////////////////////////

	//Character* testCharacter = new Character;	
	
	///////////////////////////////////////////
	//
	// 기능 변수 및 함수
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

	sf::Text debugAlphaVersionInfo(L"This game is now currently development", fontEnglish);
	debugAlphaVersionInfo.setFillColor(sf::Color(255U, 0U, 0U));
	

	//윈도우 루프 시작

	while (window.isOpen())
	{
		sf::Event event;

		///////////////////////////////////////////
		//
		// 
		// SFML 이벤트
		//
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
					//testCharacter->Jump();

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
		// 
		// 키보드/마우스 이벤트 - deltatime
		//
		// 
		///////////////////////////////////////////	

		float deltatime = clock.restart().asSeconds();

		if (isTestStage)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				//testCharacter->Move(event.key.code, deltatime);
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
			//Sprite 정보 변경

			spriteTitleBG.setScale(sf::Vector2f(window.getSize().x / spriteTitleBG.getLocalBounds().width,
				window.getSize().y / spriteTitleBG.getLocalBounds().height));
						
			//Text 정보 변경

			titleButtonDistance = 120.f * (window.getSize().x / 1920.f);
			titleButtonY = static_cast<unsigned int> (window.getSize().y * (3.f / 4.f));

			debugAlphaVersionInfo.setCharacterSize(static_cast<unsigned int>(30 * (window.getSize().x / 1920.f)));

			buttonTitleNewGame.Update(window);
			buttonTitleContinue.Update(window);
			buttonTitleOptions.Update(window);
			buttonTitleExit.Update(window);
			
			buttonTitleContinue.setPosition(
				sf::Vector2f(window.getSize().x / 2 - buttonTitleContinue.width,
				titleButtonY));

			buttonTitleNewGame.setPosition(
				sf::Vector2f(buttonTitleContinue.left - (titleButtonDistance + buttonTitleNewGame.width),
				titleButtonY));

			buttonTitleOptions.setPosition(
				sf::Vector2f(buttonTitleContinue.right + titleButtonDistance,
				titleButtonY));

			buttonTitleExit.setPosition(
				sf::Vector2f(buttonTitleOptions.right + titleButtonDistance,
				titleButtonY));
			
			//View 사이즈 변경

			sf::FloatRect visibleArea(0.f, 0.f, window.getSize().x, window.getSize().y);
			window.setView(sf::View(visibleArea));

			//testCharacter->Update(window);

			isWindowCreate = false;
		}


		///////////////////////////////////////////
		//
		// 
		// 윈도우 그리기
		//
		// 
		/////////////////////////////////////////////

		window.clear();

		if (isTitleScene)
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
		}

		if (isTestStage)
		{

			if (isSceneSwitch)
			{
				backgroundmusic.stop();
				backgroundmusic.openFromFile(MUSIC_RESOURCE"test.ogg");
				backgroundmusic.play();
				isSceneSwitch = false;
			}

			//testCharacter->Draw(window);
		}

		window.draw(debugAlphaVersionInfo);
		window.display();
	}

	return EXIT_SUCCESS;
}