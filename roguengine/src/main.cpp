#include <PCH.h>
#include <Engine.h>


// Entry point of the Engine.
int main()
{
	/*
	// Set a random seed.
	srand(static_cast<unsigned int>(time(nullptr)));

	// Create the main game object.
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1.5 * 960, 1.5 * 544, desktop.bitsPerPixel), "Rogue Ngine", sf::Style::Default);


	World game(&window);

	// Initialize and run the game object.
	game.Init();
	game.Run();

	*/

	Engine app;

	app.run();


	// Exit the application.
	return 0;

}

