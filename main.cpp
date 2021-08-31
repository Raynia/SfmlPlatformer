#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <vector>

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
	if (!fontEnglish.loadFromFile("c:/windows/fonts/arial.ttf") ||
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


	///////////////////////////////////////////
	//
	// 게임 내에서 사용되는 오브젝트 변수 및 함수
	//
	///////////////////////////////////////////

	/* 그래픽 오브젝트 (Texture -> Sprite - > Font) */

	sf::Texture texture1;
	sf::Texture texture2;

	if (!texture1.loadFromFile("resource/background_test.jpg") ||
		!texture2.loadFromFile("resource/logo_1.jpg"))
		return EXIT_FAILURE;

	texture1.setSmooth(true);
	texture2.setSmooth(true);

	sf::Sprite sprite1;
	sf::Sprite sprite2;

	sprite1.setTexture(texture1);
	sprite2.setTexture(texture2);

	/* 
	사운드 오브젝트 
	- 배경음 등 파일 크기가 큰 오브젝트는 필요한 Scene에서 sf::Music으로 로딩
	- 파일 크기가 작은 오브젝트는 sf::SoundBuffer에 저장 후 sf::Sound에 로딩	
	*/

	sf::SoundBuffer soundeffectClick;
	sf::SoundBuffer soundeffectDecide;
	sf::Music backgroundmusic;
	sf::Sound soundeffect;

	if (!soundeffectClick.loadFromFile("resource/click.wav") ||
		!soundeffectDecide.loadFromFile("resource/decide.wav"))
		return EXIT_FAILURE;

	backgroundmusic.setVolume(50.f);
	soundeffect.setVolume(50.f);

	sf::Vector2u titleUISize(100u, 40u);
	sf::Vector2u titleUIPosition(910u, 500u);
	sf::Rect<unsigned int> rect(titleUIPosition, titleUISize);
	
	///////////////////////////////////////////
	//
	// 세부 구현을 위한 변수 및 함수
	// 
	///////////////////////////////////////////

	sf::Clock clock;

	///////////////////////////////////////////
	//
	// 기능 테스트를 위한 변수 및 함수
	//
	// - 해당 변수가 사용된 모든 변수와 함수는 기능 테스트 목적을 위함
	// - 
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

	testTextMenuButton.setFont(fontEnglish);
	testTextMenuButton.setString(L"Button");	
	
	sf::Texture testTextureStart, testTextureOptions, testTextureExtra, testTextureExit;
	if (!testTextureStart.loadFromFile("resource/testStartImage.png") ||
		!testTextureOptions.loadFromFile("resource/testOptionsImage.png") ||
		!testTextureExtra.loadFromFile("resource/testExtraImage.png") ||
		!testTextureExit.loadFromFile("resource/testExitImage.png"))
		return EXIT_FAILURE;

	sf::Sprite testSpriteStart, testSpriteOptions, testSpriteExtra, testSpriteExit;
	testSpriteStart.setTexture(testTextureStart);
	testSpriteOptions.setTexture(testTextureOptions);
	testSpriteExtra.setTexture(testTextureExtra);
	testSpriteExit.setTexture(testTextureExit);

	sf::Sprite testSpriteforView;
	testSpriteforView.setTexture(texture2);


	float testMenuButtonBetweenDistance = 100.f;
	float testMenuButtonPositionY = 0.f;	

	sf::Rect<float> testRect;
	testRect = sf::FloatRect();

	//윈도우 루프 시작

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

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
					if (testScene1 && !testScene2)
					{
						testScene1 = false;
						testScene2 = true;
					}
					else/*if (!scene1 && scene2)*/
					{
						testScene1 = true;
						testScene2 = false;
					}
					isSceneSwitch = true;
				}

				if (event.key.code == sf::Keyboard::F)
				{
					if (testTitleOptionSwitch)
						testTitleOptionSwitch = false;
					else
						testTitleOptionSwitch = true;
				}
				break;

			case sf::Event::MouseButtonPressed:
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
			sprite1.setScale(sf::Vector2f(window.getSize().x / sprite1.getLocalBounds().width,
				window.getSize().y / sprite1.getLocalBounds().height));
			sprite2.setScale(sf::Vector2f(window.getSize().x / sprite1.getLocalBounds().width,
				window.getSize().y / sprite1.getLocalBounds().height));
			testSpriteforView.setScale(sf::Vector2f(window.getSize().x / sprite1.getLocalBounds().width,
				window.getSize().y / sprite1.getLocalBounds().height));

			std::cout << sprite2.getLocalBounds().width << "&" << sprite2.getLocalBounds().height << "\n";
			std::cout << sprite2.getGlobalBounds().width << "&" << sprite2.getGlobalBounds().height << "\n";
			testSpriteforView.setPosition(sf::Vector2f(sprite2.getGlobalBounds().width, 0));

			/*testSpriteStart.setScale(sf::Vector2f(window.getSize().x / testSpriteStart.getGlobalBounds().width,
				window.getSize().y / sprite1.getLocalBounds().height));*/
				/*testSpriteOptions.setScale(sf::Vector2f(window.getSize().x / testSpriteOptions.getLocalBounds().width,
					window.getSize().y / sprite1.getLocalBounds().height));*/

			testMenuButtonPositionY = (window.getSize().y / 4 * 3) - (testSpriteStart.getLocalBounds().height / 2);
			testMenuButtonBetweenDistance = testSpriteStart.getLocalBounds().width / 2;

			testSpriteStart.setPosition(
				((window.getSize().x / 2) - testSpriteStart.getLocalBounds().width * 1.5) - testMenuButtonBetweenDistance,
				testMenuButtonPositionY);

			testSpriteOptions.setPosition(
				testSpriteStart.getPosition().x + testSpriteStart.getLocalBounds().width + testMenuButtonBetweenDistance,
				testMenuButtonPositionY);

			testSpriteExit.setPosition(
				testSpriteOptions.getPosition().x + testSpriteStart.getLocalBounds().width + testMenuButtonBetweenDistance,
				testMenuButtonPositionY);

			testRect = testSpriteStart.getLocalBounds();

			sf::FloatRect visibleArea(window.getSize().x / 2, 0.f, window.getSize().x, window.getSize().y);
			window.setView(sf::View(visibleArea));

			isWindowCreate = false;
		}

		//
		
		float deltatime = clock.restart().asSeconds();

		//오브젝트가 윈도우에 그려지는 구간

		window.clear();
		
		if (testScene1)
		{			
			window.draw(sprite1);
			window.draw(testSpriteStart);
			window.draw(testSpriteOptions);
			window.draw(testSpriteExit);
			window.draw(testSpriteforView);
			if (isSceneSwitch)
			{
				backgroundmusic.stop();
				backgroundmusic.openFromFile("resource/title.ogg");
				backgroundmusic.play();
				isSceneSwitch = false;
			}

			if (testTitleOptionSwitch)
				window.draw(testTextOptions);
		}

		if (testScene2)
		{
			window.draw(sprite2);

			if (isSceneSwitch)
			{
				backgroundmusic.stop();
				backgroundmusic.openFromFile("resource/test.ogg");
				backgroundmusic.play();
				isSceneSwitch = false;
			}
		}

		window.display();
	}

	return EXIT_SUCCESS;
}