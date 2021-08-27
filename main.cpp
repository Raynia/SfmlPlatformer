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
	// Define application window attritubes
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
	// Initalize the window of the application
	//
	///////////////////////////////////////////
	sf::RenderWindow window;
	window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, windowWindowScreen, windowContextAttr);

	///////////////////////////////////////////
	//
	// Game Switch
	//
	///////////////////////////////////////////

	bool isFull = false;
	bool isCreate = true;
	bool sceneSwitch = true;

	bool scene1 = true;
	bool scene2 = false;

	bool titleOptionSwitch = false;
	bool titleStartSwitch = false;
	bool titleHideSwitch = false;


	///////////////////////////////////////////
	//
	// Game objects setting
	//
	///////////////////////////////////////////

	/* Grahpic objects */

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

	/* Sound objects */

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
	// Define test variables or vunctions
	//
	///////////////////////////////////////////
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

	float testMenuButtonBetweenDistance = 100.f;
	float testMenuButtonPositionY = 0.f;	

	sf::Rect<float> testRect;
	testRect = sf::FloatRect();

	sf::View testView(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
	window.setView(testView);
	
	
	///////////////////////////////////////////
	////
	//// 
	////
	///////////////////////////////////////////
	while (window.isOpen())
	{
		//Define all event 

		sf::Event event;

		//Window depedence event
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			//Window recreating test
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::S && !isFull)
				{
					window.create(sf::VideoMode::getDesktopMode(), windowTitle, windowFullScreen, windowContextAttr);
					isFull = true;
					isCreate = true;
				}
				
				else if (event.key.code == sf::Keyboard::S && isFull)
				{
					window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, windowWindowScreen, windowContextAttr);
					isFull = false;
					isCreate = true;
				}

				if (event.key.code == sf::Keyboard::D)
				{
					if (scene1 && !scene2)
					{
						scene1 = false;
						scene2 = true;
					}
					else/*if (!scene1 && scene2)*/
					{
						scene1 = true;
						scene2 = false;
					}
					sceneSwitch = true;
				}

				if (event.key.code == sf::Keyboard::F)
				{
					if (titleOptionSwitch)
						titleOptionSwitch = false;
					else
						titleOptionSwitch = true;
				}
				break;

			case sf::Event::MouseButtonPressed:
				break;

			default:
				break;
			}			
		}

		//

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			testCount++;
			std::cout << "testCount: " << testCount << "\n";
			if (testCount > 5000)
				testCount = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			testView.move(sf::Vector2f(10.f, 0.f));
		}

		if (isCreate)
		{
			sprite1.setScale(sf::Vector2f(window.getSize().x / sprite1.getLocalBounds().width,
				window.getSize().y / sprite1.getLocalBounds().height));
			sprite2.setScale(sf::Vector2f(window.getSize().x / sprite1.getLocalBounds().width,
				window.getSize().y / sprite1.getLocalBounds().height));
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

			isCreate = false;
		}
		
		window.clear();
		
		if (scene1)
		{			
			window.draw(sprite1);
			window.draw(testSpriteStart);
			window.draw(testSpriteOptions);
			window.draw(testSpriteExit);
			if (sceneSwitch)
			{
				backgroundmusic.stop();
				backgroundmusic.openFromFile("resource/title.ogg");
				backgroundmusic.play();
				sceneSwitch = false;
			}

			if (titleOptionSwitch)
				window.draw(testTextOptions);
		}

		if (scene2)
		{
			window.draw(sprite2);

			if (sceneSwitch)
			{
				backgroundmusic.stop();
				backgroundmusic.openFromFile("resource/test.ogg");
				backgroundmusic.play();
				sceneSwitch = false;
			}
		}

		window.display();
	}

	return EXIT_SUCCESS;
}