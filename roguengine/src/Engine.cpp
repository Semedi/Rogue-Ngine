#include <PCH.h>
#include <Engine.h>

/*
#include <Book/Utility.hpp>
#include <Book/State.hpp>
#include <Book/StateIdentifiers.hpp>
#include <Book/TitleState.hpp>
#include <Book/GameState.hpp>
#include <Book/MenuState.hpp>
#include <Book/PauseState.hpp>

*/
const sf::Time Engine::TimePerFrame = sf::seconds(1.f / 60.f);

Engine::Engine()
	:_window(sf::VideoMode(1.5 * 960, 1.5 * 544, sf::VideoMode::getDesktopMode().bitsPerPixel), "Rogue Ngine", sf::Style::Default)
	,_world(&_window)
{

	srand(static_cast<unsigned int>(time(nullptr)));
	// Enable VSync.
	_window.setVerticalSyncEnabled(true);

	// Hide the mouse cursor.
	_window.setMouseCursorVisible(false);

	_world.Init();
	
}
/*
Engine::Engine()
	: mWindow(sf::VideoMode(640, 480), "States", sf::Style::Close)
	, mTextures()
	, mFonts()
	, mPlayer()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::Main, "Media/Sansation.ttf");
	mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);
}
*/


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
			update(TimePerFrame, TimePerFrame.asSeconds());
		}


		render(dt.asSeconds());


	}

	ImGui::SFML::Shutdown();
}



void Engine::update(sf::Time dt, float frametime)
{
	_world.Update(frametime, dt);
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

/*
void Engine::update(sf::Time dt)
{
	mStateStack.update(dt);
}
*/
void Engine::render(float frametime)
{ 
	_window.clear(); // Clear the screen.

	_world.Draw(frametime);

	_window.display(); // Present the back-buffer to the screen.

}
/*
void Engine::updateStatistics(sf::Time dt)
{
	mStatisticsUpdateTime += dt;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Engine::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Game);
	mStateStack.registerState<PauseState>(States::Pause);
}
*/