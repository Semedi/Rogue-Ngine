#include "PCH.h"
#include "Player.h"

// Constructor.
Player::Player() :
m_attackDelta(0.f),
m_damageDelta(0.f),
m_manaDelta(0.f),
m_isAttacking(false),
m_statPoints(50),
m_canTakeDamage(true)
{
	m_class = static_cast<PLAYER_CLASS>(std::rand() % static_cast<int>(PLAYER_CLASS::COUNT));
	
	
	std::vector<std::string> paths = BuildPlayer(m_class);
	// Load textures.
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)] = TextureManager::AddTexture(paths[0]);
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_DOWN)] = TextureManager::AddTexture(paths[1]);
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_RIGHT)] = TextureManager::AddTexture(paths[2]);
	m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_LEFT)] = TextureManager::AddTexture(paths[3]);
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_UP)] = TextureManager::AddTexture(paths[4]);
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_DOWN)] = TextureManager::AddTexture(paths[5]);
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_RIGHT)] = TextureManager::AddTexture(paths[6]);
	m_textureIDs[static_cast<int>(ANIMATION_STATE::IDLE_LEFT)] = TextureManager::AddTexture(paths[7]);


	

	// Set initial sprite.
	SetSprite(TextureManager::GetTexture(m_textureIDs[static_cast<int>(ANIMATION_STATE::WALK_UP)]), false, 8, 12);
	m_currentTextureIndex = static_cast<int>(ANIMATION_STATE::WALK_UP);
	m_sprite.setOrigin(sf::Vector2f(13.f, 18.f));

	// Create the player's aim sprite.
	int textureID = TextureManager::AddTexture("../resources/ui/spr_aim.png");
	m_aimSprite.setTexture(TextureManager::GetTexture(textureID));
	m_aimSprite.setOrigin(sf::Vector2f(16.5f, 16.5f));
	m_aimSprite.setScale(2.f, 2.f);

	// Set stats.
	m_health = m_maxHealth = 100;
	m_mana = m_maxMana = 50;
	m_speed = 200;


	float attackBias = std::rand() % 101;
	float defenseBias = std::rand() % 101;
	float strenghtBias = std::rand() % 101;
	float dexteryBias = std::rand() % 101;
	float staminaBias = std::rand() % 101;

	float total = attackBias + defenseBias + strenghtBias + dexteryBias + staminaBias;

	m_attack += m_statPoints * (attackBias / total);
	m_defense += m_statPoints * (defenseBias / total);
	m_strength += m_statPoints * (strenghtBias / total);
	m_dexterity += m_statPoints * (dexteryBias / total);
	m_stamina += m_statPoints * (staminaBias / total);

	//Add transform component
	AttachComponent<Transform>();
	AttachComponent<Sprite>();

}

// Updates the player object.
void Player::Update(float timeDelta, Level& level)
{
	// Calculate movement speed based on the timeDelta since the last update.
	sf::Vector2f movementSpeed(0.f, 0.f);
	sf::Vector2f previousPosition = m_position;

	// Calculate where the current movement will put us.
	ANIMATION_STATE animState = static_cast<ANIMATION_STATE>(m_currentTextureIndex);

	if (Input::IsKeyPressed(Input::KEY::KEY_LEFT))
	{
		// Set movement speed.
		movementSpeed.x = -m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_LEFT;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_RIGHT))
	{
		// Set movement speed.
		movementSpeed.x = m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_RIGHT;
	}

	if (Input::IsKeyPressed(Input::KEY::KEY_UP))
	{
		// Set movement speed.
		movementSpeed.y = -m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_UP;
	}
	else if (Input::IsKeyPressed(Input::KEY::KEY_DOWN))
	{
		// Set movement speed.
		movementSpeed.y = m_speed * timeDelta;

		// Chose animation state.
		animState = ANIMATION_STATE::WALK_DOWN;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(movementSpeed.x, 0.0f), level))
	{
		m_position.x = previousPosition.x;
	}
	else
	{
		m_position.x += movementSpeed.x;
	}

	// Calculate horizontal movement.
	if (CausesCollision(sf::Vector2f(0.0f, movementSpeed.y), level))
	{
		m_position.y = previousPosition.y;
	}
	else
	{
		m_position.y += movementSpeed.y;
	}

	// update the sprite position
	m_sprite.setPosition(m_position);

	// Set the sprite.
	if (m_currentTextureIndex != static_cast<int>(animState))
	{
		m_currentTextureIndex = static_cast<int>(animState);
		m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));
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
			m_currentTextureIndex += 4;
			m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));

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
			m_currentTextureIndex -= 4;
			m_sprite.setTexture(TextureManager::GetTexture(m_textureIDs[m_currentTextureIndex]));

			// Start movement animations.
			SetAnimated(true);
		}
	}

	// Calculate aim based on mouse.
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	m_aimSprite.setPosition((float)mousePos.x, (float)mousePos.y);

	// Check if shooting.
	if ((m_attackDelta += timeDelta) > 0.25f)
	{
		if (Input::IsKeyPressed(Input::KEY::KEY_ATTACK))
		{
			// Mark player as attacking.
			m_isAttacking = true;
		}
	}

	// Determine if the player can take damage.
	if (!m_canTakeDamage)
	{
		if ((m_damageDelta += timeDelta) > 1.f)
		{
			m_canTakeDamage = true;
			m_damageDelta = 0.f;
		}
	}

	// Increase player mana.
	if ((m_manaDelta += timeDelta) > 0.20)
	{
		if (m_mana < m_maxMana)
		{
			m_mana += 1;
		}

		m_manaDelta = 0.f;
	}
}

// Returns a reference to the player's aim sprite.
sf::Sprite& Player::GetAimSprite()
{
	return m_aimSprite;
}

// Checks if the player is attacking.
bool Player::IsAttacking()
{
	if (m_isAttacking)
	{
		m_isAttacking = false;
		m_attackDelta = 0.f;
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
	return m_canTakeDamage;
}

// Apply the given amount of damage to the player.
void Player::Damage(int damage)
{
	m_health -= damage;

	if (m_health < 0)
	{
		m_health = 0;
	}

	m_canTakeDamage = false;
}

PLAYER_CLASS Player::GetClass() const
{
	return m_class;
}

void Player::SetRandomTraits()
{
	//generate traits..
	for (int i = 0; i < PLAYER_TRAIT_COUNT; ++i)
		m_traits[i] = static_cast<PLAYER_TRAIT>(std::rand() % static_cast<int>(PLAYER_TRAIT::COUNT));

	//Action the traits
	for (PLAYER_TRAIT trait : m_traits)
	{
		switch (trait)
		{
		case PLAYER_TRAIT::ATTACK: default:
			m_attack += rand() % 6 + 5;
			break;
		case PLAYER_TRAIT::DEFENSE:
			m_defense += std::rand() % 6 + 5;
			break;
		case PLAYER_TRAIT::STRENGTH:
			m_strength += std::rand() % 6 + 5;
			break;
		case PLAYER_TRAIT::DEXTERY:
			m_dexterity += std::rand() % 6 + 5;
			break;
		case PLAYER_TRAIT::STAMINA :
			m_stamina += std::rand() % 6 + 5;
			break;
		}
	}
}

// Checks is the given movement will result in a collision.
bool Player::CausesCollision(sf::Vector2f movement, Level& level)
{
	// Get the tiles that the four corners other player are overlapping with.
	Tile* overlappingTiles[4];
	sf::Vector2f newPosition = m_position + movement;

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
		m_strength += std::rand() % 6 + 5;
		break;
	case PLAYER_CLASS:: ARCHER:
		m_dexterity += std::rand() % 6 + 5;
		name = "archer";
		break;
	case PLAYER_CLASS::THIEF:
		name = "thief";
		m_stamina += std::rand() % 6 + 5;
		break;
	case PLAYER_CLASS::MAGE:
		m_defense += std::rand() % 6 + 5;
		name = "mage";
		break;
	}

	paths.push_back("../resources/players/" + name + "/spr_walk_up.png");
	paths.push_back("../resources/players/" + name + "/spr_walk_down.png");
	paths.push_back("../resources/players/" + name + "/spr_walk_right.png");
	paths.push_back("../resources/players/" + name + "/spr_walk_left.png");
	paths.push_back("../resources/players/" + name + "/spr_idle_up.png");
	paths.push_back("../resources/players/" + name + "/spr_idle_down.png");
	paths.push_back("../resources/players/" + name + "/spr_idle_right.png");
	paths.push_back("../resources/players/" + name + "/spr_idle_left.png");

	this->SetRandomTraits();

	return paths;
}


// Gets the player's mana.
int Player::GetMana() const
{
	return m_mana;
}

// Gets the player's max mana.
int Player::GetMaxMana() const
{
	return m_maxMana;
}

PLAYER_TRAIT * Player::GetTraits()
{
	return &m_traits[0];
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
		m_mana = manaValue;
	}
}

// Set the player's health.
void Player::SetHealth(int healthValue)
{
	m_health = healthValue;

	if (m_health > m_maxHealth)
	{
		m_health = m_maxHealth;
	}
}