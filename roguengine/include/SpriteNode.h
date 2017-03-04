#ifndef SPRITENODE_H
#define SPRITENODE_H

#include <SceneNode.h>

#include <SFML/Graphics/Sprite.hpp>


class SpriteNode : public SceneNode
{
public:
	SpriteNode();

	SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);


	void Set(const sf::Texture& texture);
	void Set(const sf::IntRect& textureRect);
	void Set(const sf::Color tileColor);
	void Set(float x, float y);

private:
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::Sprite			_Sprite;

};

#endif 