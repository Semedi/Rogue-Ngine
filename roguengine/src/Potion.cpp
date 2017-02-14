#include <PCH.h>
#include <Potion.h>

// Default constructor.
Potion::Potion() :
_attack(0),
_defense(0),
_strength(0),
_dexterity(0),
_stamina(0)
{
	// The string for the sprite path.
	std::string spriteFilePath;

	// Set the potion type.
	_potionType = static_cast<POTION>(std::rand() % static_cast<int>(POTION::COUNT));

	// Set stat modifiers, sprite file path, and item name.
	switch (_potionType)
	{
	case POTION::ATTACK:
		_dexterity = std::rand() % 11 + 5;
		spriteFilePath = "../resources/loot/potions/spr_potion_attack.png";
		break;

	case POTION::DEFENSE:
		_dexterity = std::rand() % 11 + 5;
		spriteFilePath = "../resources/loot/potions/spr_potion_defense.png";
		break;

	case POTION::STRENGTH:
		_strength = std::rand() % 11 + 5;
		spriteFilePath = "../resources/loot/potions/spr_potion_strength.png";
		break;

	case POTION::DEXTERITY:
		_dexterity = std::rand() % 11 + 5;
		spriteFilePath = "../resources/loot/potions/spr_potion_dexterity.png";
		break;

	case POTION::STAMINA:
		_stamina = std::rand() % 11 + 5;
		spriteFilePath = "../resources/loot/potions/spr_potion_stamina.png";
		break;
	}

	// Load and set sprite.
	SetSprite(TextureManager::GetTexture(TextureManager::AddTexture(spriteFilePath)), false, 8, 12.f);

	// Set the item type.
	_type = ITEM::POTION;
}

POTION Potion::GetPotionType() const
{
	return _potionType;
}

// Gets the attack value of the potion.
int Potion::GetAttack() const
{
	return _attack;
}

// Gets the defense value of the potion.
int Potion::GetDefense() const
{
	return _defense;
}

// Gets the strength value of the potion.
int Potion::GetStrength() const
{
	return _strength;
}

// Gets the dexterity value of the potion.
int Potion::GetDexterity() const
{
	return _dexterity;
}

// Gets the stamina value of the potion.
int Potion::GetStamina() const
{
	return _stamina;
}