#include <PCH.h>
#include <Key.h>

// Default constructor.
Key::Key()
{
	// Set item sprite.
	int textureID = TextureManager::AddTexture("../resources/loot/key/spr_pickup_key.png");
	SetSprite(TextureManager::GetTexture(textureID), false, 8, 12);

	// Set item name.
	SetItemName("Key");

	// Set item type.
	_type = ITEM::KEY;
	AttachComponent<Audio>()->SetSoundBuffer("../resources/sounds/snd_key_pickup.wav");

}