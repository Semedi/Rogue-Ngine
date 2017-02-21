#include <PCH.h>
#include <Engine.h>


const sf::Time Engine::TimePerFrame = sf::seconds(1.f / 60.f);

Engine::Engine()
	:_window(sf::VideoMode(1.5 * 960, 1.5 * 544, sf::VideoMode::getDesktopMode().bitsPerPixel), "Rogue Ngine", sf::Style::Default)
	,_world(&_window)
{

	//SEED: TIME_BASED
	srand(static_cast<unsigned int>(time(nullptr)));

	// Enable VSync.
	_window.setVerticalSyncEnabled(true);

	// Hide the mouse cursor.
	_window.setMouseCursorVisible(false);

	_world.Init();
	
}

void Engine::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;


	while (_window.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		ImGui::SFML::Update(_window, dt);

		//Fixed Update:
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);
		}

		//updatear estadisticas
		render(dt.asSeconds());


	}

	ImGui::SFML::Shutdown();
}



void Engine::update(sf::Time dt)
{
	_world.Update(dt);
}

void Engine::processInput()
{

	// Check if the game was closed.
	sf::Event event;
	if (_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		if ((event.type == sf::Event::Closed) || (Input::IsKeyPressed(Input::KEY::KEY_ESC)))
		{		
			_window.close();
			return;
		}
	}

}


void Engine::render(float frametime)
{ 
	_window.clear(); // Clear the screen.

	_world.Draw(frametime);

	//set  View
	//llamar al draw de la gui
	_window.display(); // Present the back-buffer to the screen.

}
