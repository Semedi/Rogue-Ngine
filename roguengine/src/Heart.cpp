#include <PCH.h>
#include <Heart.h>

// Default constructor.
Heart::Heart()
{
	// Set item sprite.
	SetSprite(TextureManager::GetTexture(TextureManager::AddTexture("../resources/loot/heart/spr_pickup_heart.png")), false, 8, 12);

	// Set health value.
	_health = 15;
	_health = std::rand() % 11 + 10;

	// Set item type.
	_type = ITEM::HEART;
}

// Returns the amount of health that the heart gives.
int Heart::GetHealth() const
{
	return _health;
}

void Heart::updateCurrent(sf::Time dt)
{ 
	Item::updateCurrent(dt);

	if (collision)
		delete this;

	
}

