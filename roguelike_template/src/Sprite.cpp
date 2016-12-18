#include "PCH.h"
#include "Sprite.h"

void Sprite::Draw(sf::RenderWindow & window, float timeDelta)
{
}

bool Sprite::SetSprite(sf::Texture & texture, bool isSmoth, int frames, int frameSpeed)
{
	return false;
}

sf::Sprite & Sprite::GetSprite()
{
	// TODO: insert return statement here
	return m_sprite;
}

int Sprite::GetFrameCount() const
{
	return 0;
}

bool Sprite::IsAnimated()
{
	return false;
}

void Sprite::SetAnimated(bool isAnimated)
{
}

void Sprite::NextFrame()
{
}
