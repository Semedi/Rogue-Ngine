#include <PCH.h>
#include <Game.h>

#include "modules/imgui/imgui-SFML.h"

// Entry point of the application.
int main()
{
	// Set a random seed.
	srand(static_cast<unsigned int>(time(nullptr)));

	// Create the main game object.
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(1.5 * 960, 1.5 * 544, desktop.bitsPerPixel), "Rogue Ngine", sf::Style::Default);
	Game game(&window);

	// Initialize and run the game object.
	game.Initialize();
	game.Run();


	// Exit the application.
	return 0;

}





/*

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::End();

		window.clear();
		window.draw(shape);
		ImGui::Render();
		window.display();
	}

	ImGui::SFML::Shutdown();
}
*/