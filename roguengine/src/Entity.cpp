#include <PCH.h>
#include <Entity.h>

// Default constructor.
Entity::Entity() :
_currentTextureIndex(static_cast<int>(ANIMATION_STATE::WALK_DOWN)),
_health(0),
_maxHealth(0),
_mana(0),
_maxMana(0),
_attack(0),
_defense(0),
_strength(0),
_dexterity(0),
_stamina(0),
_speed(0),
_velocity({0.f, 0.f})
{
}

// Override the default Object::Update function.
void Entity::Update(float timeDelta)
{
	// Choose animation state.
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(_currentTextureIndex);

	if ((_velocity.x != 0) || (_velocity.y != 0))
	{
		if (abs(_velocity.x) > abs(_velocity.y))
		{
			if (_velocity.x <= 0)
			{
				animState = ANIMATION_STATE::WALK_LEFT;
			}
			else
			{
				animState = ANIMATION_STATE::WALK_RIGHT;
			}
		}
		else
		{
			if (_velocity.y <= 0)
			{
				animState = ANIMATION_STATE::WALK_UP;
			}
			else
			{
				animState = ANIMATION_STATE::WALK_DOWN;
			}
		}
	}

	// Set animation speed.
	if ((_velocity.x == 0) && (_velocity.y == 0))
	{
		// The character is still.
		if (IsAnimated())
		{
			// Update sprite to idle version.
			_currentTextureIndex += 4;

			// Stop movement animations.
			SetAnimated(false);
		}
	}
	else
	{
		// The character is moving.
		if (!IsAnimated())
		{
			// Update sprite to walking version.
			_currentTextureIndex -= 4;

			// Start movement animations.
			SetAnimated(true);
		}
	}

	// Set the sprite.
	if (_currentTextureIndex != static_cast<int>(animState))
	{
		_currentTextureIndex = static_cast<int>(animState);
		_sprite.setTexture(TextureManager::GetTexture(_textureIDs[_currentTextureIndex]));
	}
}

// Gets the entities health.
int Entity::GetHealth() const
{
	return _health;
}

// Gets the entities max health.
int Entity::GetMaxHealth() const
{
	return _maxHealth;
}

// Gets the entities attack.
int Entity::GetAttack() const
{
	return _attack;
}

// Gets the entities defense.
int Entity::GetDefense() const
{
	return _defense;
}

// Gets the entities strength.
int Entity::GetStrength() const
{
	return _strength;
}

// Gets the entities dexterity.
int Entity::GetDexterity() const
{
	return _dexterity;
}

// Gets the entities stamina.
int Entity::GetStamina() const
{
	return _stamina;
}

// Sets the entities attack stat.
void Entity::SetAttack(int attackValue)
{
	_attack = attackValue;
}

// Sets the entities defense stat.
void Entity::SetDefense(int defenseValue)
{
	_defense = defenseValue;
}

// Sets the entities strength stat.
void Entity::SetStrength(int strengthValue)
{
	_strength = strengthValue;
}

// Sets the entities dexterity stat.
void Entity::SetDexterity(int dexterityValue)
{
	_dexterity = dexterityValue;
}

// Sets the entities stamina stat.
void Entity::SetStamina(int staminaValue)
{
	_stamina = staminaValue;
}