#ifndef ENGINE_H
#define ENGINE_H


#include <Player.h>
#include <World.h>
//#include <Book/StateStack.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Engine
{
public:
	Engine();
	void run();


private:
	void processInput();
	void update(sf::Time dt);
	void render(float frametime);

	void updateGui(sf::Time dt);
	void registerStates();

	


private:
	static const sf::Time TimePerFrame;

	sf::Clock _clk; //Aux CLK

	sf::RenderWindow _window;
	//TextureHolder			mTextures;
	//FontHolder				mFonts;
	Player _Player;

	//StateStack				mStateStack;
	World _world;
	sf::Text _StatisticsText;
	sf::Time __statisticsUpdateTime;
	std::size_t	_StatisticsNumFrames;
};

#endif