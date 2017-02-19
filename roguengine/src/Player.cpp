#include <PCH.h>
#include <Player.h>

// Constructor.
Player::Player() :
_attackDelta(0.f),
_damageDt(0.f),
_manaDt(0.f),
_attacking(false),
_statPoints(50),
_canTakeDamage(true)
{
	_class = static_cast<PLAYER_CLASS>(std::rand() % static_cast<int>(PLAYER_CLASS::COUNT));
	
	
	std::vector<std::string> paths = BuildPlayer(_class);
	// Load textures.
	_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(paths[0]);
	_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(paths[1]);
	_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(paths[2]);
	_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(paths[3]);
	_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(paths[4]);
	_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(paths[5]);
	_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(paths[6]);
	_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(paths[7]);


	

	//with SetSprite method we can initizialice important properties of the entity as frames_per_animation or velocity
	// Set initial sprite.
	SetSprite(TextureManager::GetTexture(_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 3, 12);
	_currentTextureIndex = static_cast<int>(ANIMATION_STATE::WALK_UP);
	_sprite.setOrigin(sf::Vector2f(13.f, 18.f));

	// Create the player's aim sprite.
	int textureID = TextureManager::AddTexture("../resources/ui/spr_aim.png");
	_aimSprite.setTexture(TextureManager::GetTexture(textureID));
	_aimSprite.setOrigin(sf::Vector2f(16.5f, 16.5f));
	_aimSprite.setScale(2.f, 2.f);

	// Set stats.
	_health = _maxHealth = 100;
	_mana = _maxMana = 50;
	_speed = 200;


	float attackBias = std::rand() % 101;
	float defenseBias = std::rand() % 101;
	float strenghtBias = std::rand() % 101;
	float dexteryBias = std::rand() % 101;
	float staminaBias = std::rand() % 101;

	float total = attackBias + defenseBias + strenghtBias + dexteryBias + staminaBias;

	_attack += _statPoints * (attackBias / total);
	_defense += _statPoints * (defenseBias / total);
	_strength += _statPoints * (strenghtBias / total);
	_dexterity += _statPoints * (dexteryBias / total);
	_stamina += _statPoints * (staminaBias / total);

	//Add transform component
	AttachComponent<Sprite>();
	AttachComponent<Audio>()->SetSoundBuffer("../resources/sounds/snd_player_hit.wav");

}

// Updates the player object.
void Player::Update(float timeDelta, Level& level)
{
	// Calculate movement speed based on the timeDelta since the last update.
	sf::Vector2f movementSpeed(0.f, 0.f);


	sf::Vector2f previousPosition = transform.position;

	// Calculate where the current movement will put us.
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(_currentTextureIndex);

	if (Input::IsKeyPressed(Input::KEY::KEY_LEFT))
	{
		// Set movement speed.
		movementSpeed.x = -_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_LEFT;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_RIGHT))
	{
		// Set movement speed.
		movementSpeed.x = _speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_RIGHT;
	}

	if (Input::IsKeyPressed(Input::KEY::KEY_UP))
	{
		// Set movement speed.
		movementSpeed.y = -_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_UP;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_DOWN))
	{
		// Set movement speed.
		movementSpeed.y = _speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_DOWN;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(movementSpeed.x, 0.0f), level))
	{
		transform.position.x = previousPosition.x;
	}
	else
	{
		transform.position.x += movementSpeed.x;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(0.0f, movementSpeed.y), level))
	{
		transform.position.y = previousPosition.y;
	}
	else
	{
		transform.position.y += movementSpeed.y;
	}

	// update the sprite position
	_sprite.setPosition(transform.position);

	// Set the sprite.
	if (_currentTextureIndex != static_cast<int>(animState))
	{
		_currentTextureIndex = static_cast<int>(animState);
		_sprite.setTexture(TextureManager::GetTexture(_textureIDs[_currentTextureIndex]));
	}

	// set animation speed
	if ((movementSpeed.x == 0) && (movementSpeed.y == 0))
	{
		// the character is still
		if (IsAnimated())
		{
			// Update sprite to idle version.
			// In our enum we have 4 walking sprites followed by 4 idle sprites.
			// Given this, we can simply add 4 to a walking sprite to get its idle counterpart.
			_currentTextureIndex += 4;
			_sprite.setTexture(TextureManager::GetTexture(_textureIDs[_currentTextureIndex]));

			// Stop movement animations.
			SetAnimated(false);
		}
	}
	else
	{
		// the character is moving
		if (!IsAnimated())
		{
			// Update sprite to walking version.
			_currentTextureIndex -= 4;
			_sprite.setTexture(TextureManager::GetTexture(_textureIDs[_currentTextureIndex]));

			// Start movement animations.
			SetAnimated(true);
		}
	}

	// Calculate aim based on mouse.
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	_aimSprite.setPosition((float)mousePos.x, (float)mousePos.y);

	// Check if shooting.
	if ((_attackDelta += timeDelta) > 0.25f)
	{
		if (Input::IsKeyPressed(Input::KEY::KEY_ATTACK))
		{
			// Mark player as attacking.
			_attacking = true;
		}
	}

	// Determine if the player can take damage.
	if (!_canTakeDamage)
	{
		if ((_damageDt += timeDelta) > 1.f)
		{
			_canTakeDamage = true;
			_damageDt = 0.f;
		}
	}

	// Increase player mana.
	if ((_manaDt += timeDelta) > 0.20)
	{
		if (_mana < _maxMana)
		{
			_mana += 1;
		}

		_manaDt = 0.f;
	}
}

// Returns a reference to the player's aim sprite.
sf::Sprite& Player::GetAimSprite()
{
	return _aimSprite;
}

// Checks if the player is attacking.
bool Player::IsAttacking()
{
	if (_attacking)
	{
		_attacking = false;
		_attackDelta = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

// Checks if the player can take damage.
bool Player::CanTakeDamage()
{
	return _canTakeDamage;
}

// Apply the given amount of damage to the player.
void Player::Damage(int damage)
{
	_health -= damage;

	if (_health < 0)
	{
		_health = 0;
	}

	_canTakeDamage = false;
}

PLAYER_CLASS Player::GetClass() const
{
	return _class;
}

void Player::SetRandomTraits()
{
	//generate traits..
	for (int i = 0; i < PLAYER_TRAIT_COUNT; ++i)
		_traits[i] = static_cast<PLAYER_TRAIT>(std::rand() % static_cast<int>(PLAYER_TRAIT::COUNT));

	//Action the traits
	for (PLAYER_TRAIT trait : _traits)
	{
		switch (trait)
		{
		case PLAYER_TRAIT::ATTACK: default:
			_attack += rand() % 6 + 5;
			break;
		case PLAYER_TRAIT::DEFENSE:
			_defense += std::rand() % 6 + 5;
			break;
		case PLAYER_TRAIT::STRENGTH:
			_strength += std::rand() % 6 + 5;
			break;
		case PLAYER_TRAIT::DEXTERY:
			_dexterity += std::rand() % 6 + 5;
			break;
		case PLAYER_TRAIT::STAMINA :
			_stamina += std::rand() % 6 + 5;
			break;
		}
	}
}

// Checks is the given movement will result in a collision.
bool Player::CausesCollision(sf::Vector2f movement, Level& level)
{
	// Get the tiles that the four corners other player are overlapping with.
	Tile* overlappingTiles[4];
	sf::Vector2f newPosition = transform.position + movement;

	// Top left.
	overlappingTiles[0] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y - 14.f));

	// Top right.
	overlappingTiles[1] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y - 14.f));

	// Bottom left.
	overlappingTiles[2] = level.GetTile(sf::Vector2f(newPosition.x - 14.f, newPosition.y + 14.f));

	// Bottom right.
	overlappingTiles[3] = level.GetTile(sf::Vector2f(newPosition.x + 14.f, newPosition.y + 14.f));

	// If any of the overlapping tiles are solid there was a collision.
	for (int i = 0; i < 4; i++)
	{
		if (level.IsSolid(overlappingTiles[i]->columnIndex, overlappingTiles[i]->rowIndex))
			return true;
	}

	// If we've not returned yet no collisions were found.
	return false;
}

std::vector<std::string> Player::BuildPlayer(PLAYER_CLASS c)
{
	std::vector<std::string> paths;
	std::string name = "";

	switch (c){
	case PLAYER_CLASS::WARRIOR:
		name = "warrior";
		_strength += std::rand() % 6 + 5;
		break;
	case PLAYER_CLASS:: ARCHER:
		_dexterity += std::rand() % 6 + 5;
		name = "archer";
		break;
	case PLAYER_CLASS::THIEF:
		name = "thief";
		_stamina += std::rand() % 6 + 5;
		break;
	case PLAYER_CLASS::MAGE:
		_defense += std::rand() % 6 + 5;
		name = "mage";
		break;
	}

	/*
	paths.push_back("../resources/players/" + name + "/spr_walk_up.png");
	paths.push_back("../resources/players/" + name + "/spr_walk_down.png");
	paths.push_back("../resources/players/" + name + "/spr_walk_right.png");
	paths.push_back("../resources/players/" + name + "/spr_walk_left.png");
	paths.push_back("../resources/players/" + name + "/spr_idle_up.png");
	paths.push_back("../resources/players/" + name + "/spr_idle_down.png");
	paths.push_back("../resources/players/" + name + "/spr_idle_right.png");
	paths.push_back("../resources/players/" + name + "/spr_idle_left.png");
	*/

	paths.push_back("../resources/players/mario/player_v_u.png");
	paths.push_back("../resources/players/mario/player_v_d.png");
	paths.push_back("../resources/players/mario/player_h_r.png");
	paths.push_back("../resources/players/mario/player_h_l.png");
	paths.push_back("../resources/players/mario/player_u.png");
	paths.push_back("../resources/players/mario/player_d.png");
	paths.push_back("../resources/players/mario/player_r.png");
	paths.push_back("../resources/players/mario/player_l.png");

	this->SetRandomTraits();

	return paths;
}


// Gets the player's mana.
int Player::GetMana() const
{
	return _mana;
}

// Gets the player's max mana.
int Player::GetMaxMana() const
{
	return _maxMana;
}

PLAYER_TRAIT * Player::GetTraits()
{
	return &_traits[0];
}

int Player::GetTraitCount()
{
	return PLAYER_TRAIT_COUNT;
}

// Set the player's mana level.
void Player::SetMana(int manaValue)
{
	if (manaValue >= 0)
	{
		_mana = manaValue;
	}
}

// Set the player's health.
void Player::SetHealth(int healthValue)
{
	_health = healthValue;

	if (_health > _maxHealth)
	{
		_health = _maxHealth;
	}
}