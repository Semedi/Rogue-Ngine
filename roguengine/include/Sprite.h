#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <Component.h>

class Sprite : public Component
{
	public:
		virtual void Draw(sf::RenderWindow &window, float timeDelta);
		bool SetSprite(sf::Texture& texture, bool isSmoth, int frames = 1, int frameSpeed = 0);
		sf::Sprite& GetSprite();
		int GetFrameCount() const;
		bool IsAnimated();
		void SetAnimated(bool isAnimated);

	protected:
		sf::Sprite m_sprite;

	private:

		void NextFrame();

private:
	int _animationSpeed;
	bool _animated;
	int _nframe;
	int _currentFrame;
	int _frameWidth;
	int _frameHeight;



};



#endif