#include <SpriteNode.h>

#include <SFML/Graphics/RenderTarget.hpp>

SpriteNode::SpriteNode() {}
SpriteNode::SpriteNode(const sf::Texture& texture)
	: _Sprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
	: _Sprite(texture, textureRect)
{
}

void SpriteNode::Set(const sf::Texture & texture)
{
	_Sprite.setTexture(texture);
}

void SpriteNode::Set(const sf::IntRect & textureRect)
{
	_Sprite.setTextureRect(textureRect);
}

void SpriteNode::Set(const sf::Color tileColor)
{
	_Sprite.setColor(tileColor);
}

void SpriteNode::Set(float x, float y)
{
	_Sprite.setPosition(x, y);
}

sf::Sprite SpriteNode::Get()
{
	return _Sprite;
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_Sprite, states);
}