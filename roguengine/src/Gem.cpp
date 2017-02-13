#include <PCH.h>
#include <Gem.h>

// Default Constructor.
Gem::Gem()
{
	// Set the sprite.
	SetSprite(TextureManager::GetTexture(TextureManager::AddTexture("../resources/loot/gem/spr_pickup_gem.png")), false, 8, 12);

	// Set the value of the gem.
	_scoreValue = 50;
	_scoreValue = std::rand() % 100;
	// Set the item type.
	_type = ITEM::GEM;

	AttachComponent<Audio>()->SetSoundBuffer("../resources/sounds/snd_gem_pickup.wav");
	
	
	
}

// Gets the amount of score this pickup gives.
int Gem::GetScoreValue() const
{
	return _scoreValue;
}