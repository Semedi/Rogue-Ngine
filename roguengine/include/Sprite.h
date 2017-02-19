#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include <Component.h>
#include <SceneNode.h>

class Sprite : public Component, public SceneNode
{
public:

	Sprite();
	explicit Sprite(const sf::Texture& texture);
	Sprite(const sf::Texture& texture, const sf::IntRect& textureRect);


	virtual void Draw(sf::RenderWindow &window, float timeDelta);
	bool SetSprite(sf::Texture& texture, bool isSmoth, int frames = 1, int frameSpeed = 0);
	sf::Sprite& GetSprite();
	int GetFrameCount() const;
	bool IsAnimated();
	void SetAnimated(bool isAnimated);



private:

	void NextFrame();
	virtual void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	sf::Sprite _sprite;

private:


	int _animationSpeed;
	bool _animated;
	int _nframe;
	int _currentFrame;
	int _frameWidth;
	int _frameHeight;
};
#endif