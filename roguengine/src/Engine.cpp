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
{

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

	float currentTime = _clk.restart().asSeconds();
	float timeDelta = 0.f;


	while (_window.isOpen())
	{
		sf::Time dt = clock.restart();


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


		/*
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			//if (mStateStack.isEmpty())
				//mWindow.close();
		}
		*/
		//updateStatistics(dt);

		//render();
	}
}
/*
void Engine::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Engine::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Engine::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

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