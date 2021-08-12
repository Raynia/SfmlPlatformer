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

	sf::Uint32 window_width = 1280U; //set screen width
	sf::Uint32 window_height = 720U; //set screen height
	sf::String window_title(std::string("Pong")); //set title

	sf::ContextSettings window_settings;
	window_settings.depthBits = 24U;
	window_settings.stencilBits = 8U;
	window_settings.antialiasingLevel = 4U;
	window_settings.majorVersion = 4U;
	window_settings.minorVersion = 0U;

	const int32_t window_style = sf::Style::Close;

	sf::Font font;
	if (!font.loadFromFile("c:/windows/fonts/arial.ttf"))
		return EXIT_FAILURE;

	sf::Text text("Hello SFML!", font, 30U);

	///////////////////////////////////////////
	//
	// Create the window of the application
	//
	///////////////////////////////////////////

	sf::RenderWindow window;

	window.create(sf::VideoMode(window_width, window_height), window_title, window_style, window_settings);

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

		}

		window.clear();

		window.display();
	}


	window.~RenderWindow();

	return EXIT_SUCCESS;
}