#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <ctime>

int main()
{
	///////////////////////////////////////////
	//
	// Define application window attritubes
	//
	///////////////////////////////////////////

	std::srand(static_cast<unsigned int>(std::time(NULL)));


	
	sf::Uint32 windowWidth = 1280U; //set screen width
	sf::Uint32 windowHeight = 720U; //set screen height
	sf::String windowTitle(std::string("Pong")); //set title

	sf::ContextSettings windowContextAttr;
	windowContextAttr.depthBits = 24U;
	windowContextAttr.stencilBits = 8U;
	windowContextAttr.antialiasingLevel = 4U;
	windowContextAttr.majorVersion = 4U;
	windowContextAttr.minorVersion = 0U;

	const int32_t windowStyle = sf::Style::Close;
	
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

	window.create(sf::VideoMode(windowWidth, windowHeight), windowTitle, windowStyle, windowContextAttr);

	///////////////////////////////////////////
	////
	//// Define variable or constant
	////
	///////////////////////////////////////////

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

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(textEN);
		window.draw(textKR);
		window.display();
	}


	window.~RenderWindow();

	return EXIT_SUCCESS;
}