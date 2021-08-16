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

	std::vector<sf::VideoMode> videoMode;
	videoMode = sf::VideoMode::getFullscreenModes();

	sf::Uint32 windowWidth = 1280U; //set screen width
	sf::Uint32 windowHeight = 720U; //set screen height
	sf::String windowTitle(std::string("Platformer")); //set title

	sf::ContextSettings windowContextAttr;
	windowContextAttr.depthBits = 32U;
	windowContextAttr.stencilBits = 8U;
	windowContextAttr.antialiasingLevel = 4U;
	windowContextAttr.majorVersion = 4U;
	windowContextAttr.minorVersion = 0U;

	const int32_t windowFullScreen = sf::Style::Close | sf::Style::Fullscreen;
	const int32_t windowWindowScreen = sf::Style::Close;
	
	sf::Font fontEN;
	if (!fontEN.loadFromFile("c:/windows/fonts/arial.ttf"))
		return EXIT_FAILURE;

	sf::Font fontEastAsian;
	if (!fontEastAsian.loadFromFile("c:/windows/fonts/gulim.ttc"))
		return EXIT_FAILURE;

	sf::Text textEN(L"Hello", fontEN, 30U);
	sf::Text textKR(L"¾È³ç", fontEastAsian, 30U);

	textEN.setPosition(0, 0);
	textKR.setPosition(500, 0);

	///////////////////////////////////////////
	//
	// Create the window of the application
	//
	///////////////////////////////////////////

	sf::RenderWindow window;
	window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, windowWindowScreen, windowContextAttr);

	///////////////////////////////////////////
	////
	//// Define variable or constant
	////
	///////////////////////////////////////////
	bool isFull = false;
	bool isCreate = true;

	bool scene1 = true;
	bool scene2 = false;

	sf::Texture texture1;
	sf::Texture texture2;

	if (!texture1.loadFromFile("resource/background_test.jpg"))
		return EXIT_FAILURE;	
	if (!texture2.loadFromFile("resource/logo_1.jpg"))
		return EXIT_FAILURE;

	sf::Sprite sprite1;
	sf::Sprite sprite2;
	sprite1.setTexture(texture1);
	sprite2.setTexture(texture2);

	sf::SoundBuffer soundbuffer1;
	sf::SoundBuffer soundbuffer2;

	if (!soundbuffer1.loadFromFile("resource/title.ogg"))
		return EXIT_FAILURE;
	if (!soundbuffer2.loadFromFile("resource/test.ogg"))
		return EXIT_FAILURE;

	sf::Sound sound1;
	sf::Sound sound2;
	sound1.setBuffer(soundbuffer1);
	sound1.setVolume(50.f);

	sound2.setBuffer(soundbuffer2);
	sound2.setVolume(50.f);
	///////////////////////////////////////////
	////
	//// Game objects setting
	////
	///////////////////////////////////////////		

	///////////////////////////////////////////
	////
	//// Define debug values
	////
	///////////////////////////////////////////
	//sound1.play();
	
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
				}				
				break;
			}			
		}

		//

		if (isCreate)
		{
			sprite1.setScale(sf::Vector2f(window.getSize().x / sprite1.getLocalBounds().width,
				window.getSize().y / sprite1.getLocalBounds().height));
			isCreate = false;
		}

		window.clear();
		
		if (scene1)
		{			
			window.draw(sprite1);
			window.draw(textEN);
			if (sound1.getStatus() == sf::SoundSource::Stopped)
				sound1.play();
		}

		if (scene2)
		{
			window.draw(sprite2);
			window.draw(textKR);
			if (sound2.getStatus() == sf::SoundSource::Stopped)
				sound2.play();
		}

		window.display();
	}

	return EXIT_SUCCESS;
}