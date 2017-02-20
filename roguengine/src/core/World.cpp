#include <PCH.h>
#include <World.h>


// Default constructor.
World::World(sf::RenderWindow* window) :
_window(*window),
_gameState(GAME_STATE::PLAYING),
_isRunning(true),
_string(""),
_playerPrevTile(nullptr),
_activeGoal(false),
_screenSize({ 0, 0 }),
_screenCenter({ 0, 0 }),
_scoreTotal(0),
_goldTotal(0),
_projectileTextureID(0),
_levelWasGenerated(false)
{
	
	//_window.setSize(_screenSize);
	// Calculate and store the center of the screen.
	_screenCenter = { _window.getSize().x / 2.f, _window.getSize().y / 2.f };

	// Create the level object.
	_level = Level(*window);

	// Create the game font.
	_font.loadFromFile("../resources/fonts/ADDSBP__.TTF");

	// Setup the main game music & Load the music track, play the music
	int trackIndex = std::rand() % static_cast<int>(MUSIC_TRACK::COUNT) + 1;
	_music.openFromFile("../resources/music/msc_main_track_" + std::to_string(trackIndex) + ".wav");
	//_music.play();

}

// Initializes the game.
void World::Init()
{

	ImGui::SFML::Init(_window);

	_level.AddTile("../resources/tiles/floor_alt.png", TILE::FLOOR_ALT);

	// Get the screen size.
	_screenSize = _window.getSize();

	/*to dprecate*/
	/********/

	// Load the correct projectile texture.
	//_projectileTextureID = TextureManager::AddTexture("../resources/projectiles/spr_sword.png");
	switch (_player.GetClass())
	{
	case PLAYER_CLASS::ARCHER:
		_projectileTextureID = TextureManager::AddTexture("../resources/projectiles/spr_arrow.png");
		break;
	case PLAYER_CLASS::MAGE:
		_projectileTextureID = TextureManager::AddTexture("../resources/projectiles/spr_magic_ball.png");
		break;
	case PLAYER_CLASS::THIEF:
		_projectileTextureID = TextureManager::AddTexture("../resources/projectiles/spr_dagger.png");
		break;
	case PLAYER_CLASS::WARRIOR:
		_projectileTextureID = TextureManager::AddTexture("../resources/projectiles/spr_sword.png");
		break;
	}



	// Initialize the UI.
	LoadUI();

	// Builds the light grid.
	ConstructLightGrid();

	// Define the game views.
	_views[static_cast<int>(VIEW::MAIN)] = _window.getDefaultView();
	_views[static_cast<int>(VIEW::MAIN)].zoom(0.5f);
	_views[static_cast<int>(VIEW::UI)] = _window.getDefaultView();

	// Load the level.
	//_level.LoadLevelFromFile("../resources/data/level_data.txt");
	GenerateLevel();


	//_player.SetPosition(pos);
	//SpawnRandomTiles(TILE::FLOOR_ALT, 15);
	//SpawnRandomTiles(TILE::CRATE, 15);
	//PopulateLevel();

	// Load all game sounds.
	int soundBufferId;

	// Load enemy die sound.
	
	soundBufferId = SoundBufferManager::AddSoundBuffer("../resources/sounds/snd_enemy_dead.wav", 5.0f, 80.0f);
	//_enemyDieSound.setBuffer(SoundBufferManager::GetSoundBuffer("../resources/sounds/snd_enemy_dead.wav"));
	//_enemyDieSound.setAttenuation(5.f);
	//_enemyDieSound.setMinDistance(80.f);
	

	// Load torch sound.
	soundBufferId = SoundBufferManager::AddSoundBuffer("../resources/sounds/snd_fire.wav");
	_fireSound.setBuffer(SoundBufferManager::GetSoundBuffer(soundBufferId));
	_fireSound.setLoop(true);
	_fireSound.setAttenuation(5.f);
	_fireSound.setMinDistance(80.f);
	_fireSound.play();
}

// Constructs the grid of sprites that are used to draw the game light system.
void World::ConstructLightGrid()
{
	// Load the light tile texture and store a reference.
	int textureID = TextureManager::AddTexture("../resources/spr_light_grid.png");
	sf::Texture& lightTexture = TextureManager::GetTexture(textureID);

	// Calculate the number of tiles in the grid. Each light tile is 25px square.
	sf::IntRect levelArea;

	// Define the bounds of the level.
	levelArea.left = static_cast<int>(_level.GetPosition().x);
	levelArea.top = static_cast<int>(_level.GetPosition().y);
	levelArea.width = _level.GetSize().x * _level.GetTileSize();
	levelArea.height = _level.GetSize().y * _level.GetTileSize();

	int width, height, lightTotal;

	width = levelArea.width / 25;
	height = levelArea.height / 25;

	lightTotal = width * height;

	// Create all tiles.
	for (int i = 0; i < lightTotal; i++)
	{
		// Create the tile.
		sf::Sprite lightSprite;

		// Set sprite texture.
		lightSprite.setTexture(lightTexture);

		// Set the position of the tile.
		int xPos = levelArea.left + ((i % width) * 25);
		int yPos = levelArea.top + ((i / width) * 25);

		lightSprite.setPosition(static_cast<float>(xPos), static_cast<float>(yPos));

		// Add the sprite to our light vector.
		_lightGrid.push_back(lightSprite);
	}
}

// Loads and prepares all UI assets.
void World::LoadUI()
{
	// Initialize the player ui texture and sprite.
	_playerUiSprite = std::make_shared<sf::Sprite>();
	_playerUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_warrior_ui.png")));
	_playerUiSprite->setPosition(sf::Vector2f(45.f, 45.f));
	_playerUiSprite->setOrigin(sf::Vector2f(30.f, 30.f));
	_uiSprites.push_back(_playerUiSprite);

	// Bar outlines.
	sf::Texture& barOutlineTexture = TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_bar_outline.png"));
	sf::Vector2f barOutlineTextureOrigin = { barOutlineTexture.getSize().x / 2.f, barOutlineTexture.getSize().y / 2.f };

	_healthBarOutlineSprite = std::make_shared<sf::Sprite>();
	_healthBarOutlineSprite->setTexture(barOutlineTexture);
	_healthBarOutlineSprite->setPosition(sf::Vector2f(205.f, 35.f));
	_healthBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	_uiSprites.push_back(_healthBarOutlineSprite);

	_manaBarOutlineSprite = std::make_shared<sf::Sprite>();
	_manaBarOutlineSprite->setTexture(barOutlineTexture);
	_manaBarOutlineSprite->setPosition(sf::Vector2f(205.f, 55.f));
	_manaBarOutlineSprite->setOrigin(sf::Vector2f(barOutlineTextureOrigin.x, barOutlineTextureOrigin.y));
	_uiSprites.push_back(_manaBarOutlineSprite);

	//Bars.
	sf::Texture& healthBarTexture = TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_health_bar.png"));
	sf::Vector2f barTextureOrigin = { healthBarTexture.getSize().x / 2.f, healthBarTexture.getSize().y / 2.f };

	_healthBarSprite = std::make_shared<sf::Sprite>();
	_healthBarSprite->setTexture(healthBarTexture);
	_healthBarSprite->setPosition(sf::Vector2f(205.f, 35.f));
	_healthBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	_manaBarSprite = std::make_shared<sf::Sprite>();
	_manaBarSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_mana_bar.png")));
	_manaBarSprite->setPosition(sf::Vector2f(205.f, 55.f));
	_manaBarSprite->setOrigin(sf::Vector2f(barTextureOrigin.x, barTextureOrigin.y));

	// Initialize the coin and gem ui sprites.
	_gemUiSprite = std::make_shared<sf::Sprite>();
	_gemUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_gem_ui.png")));
	_gemUiSprite->setPosition(sf::Vector2f(_screenCenter.x - 260.f, 50.f));
	_gemUiSprite->setOrigin(sf::Vector2f(42.f, 36.f));
	_uiSprites.push_back(_gemUiSprite);

	_coinUiSprite = std::make_shared<sf::Sprite>();
	_coinUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_coin_ui.png")));
	_coinUiSprite->setPosition(sf::Vector2f(_screenCenter.x + 60.f, 50.f));
	_coinUiSprite->setOrigin(sf::Vector2f(48.f, 24.f));
	_uiSprites.push_back(_coinUiSprite);

	// Key pickup sprite.
	_keyUiSprite = std::make_shared<sf::Sprite>();
	_keyUiSprite->setTexture(TextureManager::GetTexture(TextureManager::AddTexture("../resources/ui/spr_key_ui.png")));
	_keyUiSprite->setPosition(sf::Vector2f(_screenSize.x - 120.f, _screenSize.y - 70.f));
	_keyUiSprite->setOrigin(sf::Vector2f(90.f, 45.f));
	_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
	_uiSprites.push_back(_keyUiSprite);

	// Load stats.
	_attackStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_attack_ui.png");
	_attackStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_attack_ui_alt.png");

	_attackStatSprite = std::make_shared<sf::Sprite>();
	_attackStatSprite->setTexture(TextureManager::GetTexture(_attackStatTextureIDs[0]));
	_attackStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	_attackStatSprite->setPosition(sf::Vector2f(_screenCenter.x - 270.f, _screenSize.y - 30.f));
	_uiSprites.push_back(_attackStatSprite);

	_defenseStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_defense_ui.png");
	_defenseStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_defense_ui_alt.png");

	_defenseStatSprite = std::make_shared<sf::Sprite>();
	_defenseStatSprite->setTexture(TextureManager::GetTexture(_defenseStatTextureIDs[0]));
	_defenseStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	_defenseStatSprite->setPosition(sf::Vector2f(_screenCenter.x - 150.f, _screenSize.y - 30.f));
	_uiSprites.push_back(_defenseStatSprite);

	_strengthStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_strength_ui.png");
	_strengthStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_strength_ui_alt.png");

	_strengthStatSprite = std::make_shared<sf::Sprite>();
	_strengthStatSprite->setTexture(TextureManager::GetTexture(_strengthStatTextureIDs[0]));
	_strengthStatSprite->setOrigin(sf::Vector2f(22.f, 12.f));
	_strengthStatSprite->setPosition(sf::Vector2f(_screenCenter.x - 30.f, _screenSize.y - 30.f));
	_uiSprites.push_back(_strengthStatSprite);

	_dexterityStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_dexterity_ui.png");
	_dexterityStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_dexterity_ui_alt.png");

	_dexterityStatSprite = std::make_shared<sf::Sprite>();
	_dexterityStatSprite->setTexture(TextureManager::GetTexture(_dexterityStatTextureIDs[0]));
	_dexterityStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	_dexterityStatSprite->setPosition(sf::Vector2f(_screenCenter.x + 90.f, _screenSize.y - 30.f));
	_uiSprites.push_back(_dexterityStatSprite);

	_staminaStatTextureIDs[0] = TextureManager::AddTexture("../resources/ui/spr_stamina_ui.png");
	_staminaStatTextureIDs[1] = TextureManager::AddTexture("../resources/ui/spr_stamina_ui_alt.png");

	_staminaStatSprite = std::make_shared<sf::Sprite>();
	_staminaStatSprite->setTexture(TextureManager::GetTexture(_staminaStatTextureIDs[0]));
	_staminaStatSprite->setOrigin(sf::Vector2f(16.f, 16.f));
	_staminaStatSprite->setPosition(sf::Vector2f(_screenCenter.x + 210.f, _screenSize.y - 30.f));
	_uiSprites.push_back(_staminaStatSprite);

	int traitCount = _player.GetTraitCount();
	//set player traits.
	for (int i = 0; i < traitCount; i++)
	{
		switch (_player.GetTraits()[i])
		{
		case PLAYER_TRAIT::ATTACK:
			_attackStatSprite->setTexture(TextureManager::GetTexture(_attackStatTextureIDs[1]));
			_attackStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;
		case PLAYER_TRAIT::DEFENSE:
			_defenseStatSprite->setTexture(TextureManager::GetTexture(_defenseStatTextureIDs[1]));
			_defenseStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;
		case PLAYER_TRAIT::STRENGTH:
			_strengthStatSprite->setTexture(TextureManager::GetTexture(_strengthStatTextureIDs[1]));
			_strengthStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;
			
		case PLAYER_TRAIT::DEXTERY:
			_dexterityStatSprite->setTexture(TextureManager::GetTexture(_dexterityStatTextureIDs[1]));
			_dexterityStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;
		case PLAYER_TRAIT::STAMINA:
			_staminaStatSprite->setTexture(TextureManager::GetTexture(_staminaStatTextureIDs[1]));
			_staminaStatSprite->setScale(sf::Vector2f(1.2f, 1.2f));
			break;

		}

	}
	
}
// Plays the given soiund effect, with randomized parameters
void World::PlaySound(sf::Sound & sound, sf::Vector2f position)
{
	// Generate and set a random pitch.
	float pitch = (rand() % 11 + 95) / 100.f;
	sound.setPitch(pitch);

	// Set the position of the sound.
	sound.setPosition(position.x, position.y, 0.f);

	// Play the sound.
	sound.play();
}

// Populate the level with items.
void World::PopulateLevel()
{

	int iterations = std::rand() % 10 + 1;

	for (int i = 0; i < MAX_ITEM_SPAWN_COUNT; i++){

		if (std::rand() % 2)
			SpawnItem(static_cast<ITEM>(std::rand() % 2));
	}

	for (int i = 0; i < MAX_ENEMY_SPAWN_COUNT; i++) {

		if (std::rand() % 2)
			SpawnEnemy(static_cast<ENEMY>(std::rand() % static_cast<int>(ENEMY::COUNT)));
	}
}



void World::GenerateLevel()
{
	// Generate a new level.
	_level.GenerateLevel();

	// Add a key to the level.
	SpawnItem(ITEM::KEY);

	// Populate the level with items.
	PopulateLevel();

	// 1 in 3 change of creating a level goal.
	if (((std::rand() % 3) == 0) && (!_activeGoal))
	{
		GenerateLevelGoal();
	}

	// Moves the player to the start.
	_player.SetPosition(_level.SpawnLocation());
	_player.GetComponent<Transform>()->SetPosition(_level.SpawnLocation());

}

// Returns the running state of the game.
bool World::IsRunning()
{
	return _isRunning;
}


void World::processInput()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		//Player_handleEvents

		if ((event.type == sf::Event::Closed) || (Input::IsKeyPressed(Input::KEY::KEY_ESC)))
			_window.close();
		
	}
}

// Updates the game.
void World::Update(float timeDelta, sf::Time dt)
{
	// Check what state the game is in.
	switch (_gameState)
	{
	case GAME_STATE::MAIN_MENU:
		// Main menu code ...
		break;

	case GAME_STATE::PLAYING:
	{


		ImGui::SFML::Update(_window, dt);
		// First check if the player is at the exit. If so there's no need to update anything.
		Tile& playerTile = *_level.GetTile(_player.GetPosition());
		//_posTile& playerTile = *_level.GetTile(_player.transform.GetPosition());

		/* THE PLAYER ENTER IN A NEW AREA*/
		if (playerTile.type == TILE::WALL_DOOR_UNLOCKED)
		{

			//flush and generate random!
			_items.clear();
			_enemies.clear();
			GenerateLevel();
			_keyUiSprite->setColor(sf::Color(255, 255, 255, 60));
		}
		else
		{

			/* COMMANDQUEUE ACTIVART EVENTOS*/
			// Update the player.
			_player.Update(timeDelta, _level);

			// Store the player position as it's used many times.
			sf::Vector2f playerPosition = _player.GetPosition();
			//_possf::Vector2f playerPosition = _player.GetComponent<Transform>()->GetPosition();

			// move the listener to players location.
			sf::Listener::setPosition(playerPosition.x, playerPosition.y, 0.f);



			// If the player is attacking create a projectile.
			if (_player.IsAttacking())
			{
				if (_player.GetMana() >= 2)
				{
					sf::Vector2f target(static_cast<float>(sf::Mouse::getPosition().x), static_cast<float>(sf::Mouse::getPosition().y));
					std::unique_ptr<Projectile> proj = std::make_unique<Projectile>(TextureManager::GetTexture(_projectileTextureID), playerPosition, _screenCenter, target);
					_playerProjectiles.push_back(std::move(proj));

					// Reduce player mana.
					_player.SetMana(_player.GetMana() - 2);
				}
			}
			/*******************************************/

			// UPDATE DEL GRAFO DE LA ESCENA
			/* UPDATE PART*/
			// Update all items.
			UpdateItems(playerPosition);

			// Update level light.
			UpdateLight(playerPosition);

			// Update all enemies.
			UpdateEnemies(playerPosition, timeDelta);

			// Update all projectiles.
			UpdateProjectiles(timeDelta);

			/*********************************************/



			/*
			* AMBIANCE =================================================================================
			*/

			// Find the nearest torch 4 playing de sound
			auto torches = _level.GetTorches();

			if (!torches->empty())
			{
				//Store the closest torch
				std::shared_ptr<Torch> nearestTorch = torches->front();
				float lowestDistanceToPlayer = DistanceBetweenPoints(playerPosition, nearestTorch->GetPosition());

				for (std::shared_ptr<Torch> torch : *torches)
				{
					//Distance to player
					float distanceToPlayer = DistanceBetweenPoints(playerPosition, torch->GetPosition());
					if (distanceToPlayer < lowestDistanceToPlayer)
					{
						lowestDistanceToPlayer = distanceToPlayer;
						nearestTorch = torch;
					}
				}
				_fireSound.setPosition(nearestTorch->GetPosition().x, nearestTorch->GetPosition().y, 0.0f);

			}

			/**                           LLAMAMOS A LA INTELIGENCIA ARTIFICIAL DEL ENEMIGO solo si
			*********************************************************************************************
			*********************************************************************************************
			*/
			// Check if the player has moved grid square.
			Tile* playerCurrentTile = _level.GetTile(playerPosition);
			if (_playerPrevTile != playerCurrentTile)
			{
				// Store the new tile.
				_playerPrevTile = playerCurrentTile;

				// Update path finding for all enemies if within range of the player.
				for (const auto& enemy : _enemies)
				{
					/* vision 4 the enemy? 
					   we check 4 every position the actual distance between player and enemy
					   if is less than 300.f we call pathfinding
					*/
					if (DistanceBetweenPoints(enemy->GetPosition(), playerPosition) < 300.f)
					{
						enemy->UpdatePathfinding(_level, playerPosition);
					}
				}
			}

			//==========================================================================================


			/*
			*QUEST COMPLETION SYSTEM =========================================================================================================================================================
			*/
			// Check if we have completed an active goal.
			if (_activeGoal)
			{


				if ((_gemGoal <= 0) &&
					(_goldGoal <= 0) &&
					(_killGoal <= 0))
				{
					_scoreTotal += std::rand() % 1001 + 1000;
					_activeGoal = false;
				}
				else
				{



					std::ostringstream ss;

					if (_goldGoal > 0)
					{
						ss << "Current Goal: Collect " << _goldGoal << " gold" << "!" << std::endl;
					}
					else if (_gemGoal > 0)
					{
						ss << "Current Goal: Collect " << _gemGoal << " gem" << "!" << std::endl;
					}
					else if (_killGoal > 0)
					{
						ss << "Current Goal: Kill " << _killGoal << " enemies" << "!" << std::endl;
					}
					_goalString = ss.str();
					/* NEW GUI, DEBUG PURPOSES !*/
					ImGui::Begin("Bienvenido a Rogue Ngine!");
					ImGui::Text("Eres un parguelon, hijo puta ha ve si aprendeeeeeeeh");
					ImGui::Text("y por eso te voy a mandar esta tarea:");
					ImGui::Text(ss.str().c_str());
					ImGui::End();

				}

			}
			//=============================================================================================================================================================================

			/* LAST INSTRUCTION*/
			// AdaptPlayerPosition();
			// Center the view.
			_views[static_cast<int>(VIEW::MAIN)].setCenter(playerPosition);
		}
	}
	break;

	case GAME_STATE::GAME_OVER:
		// Game over code
		break;
	}
}

// Updates the level light.
void World::UpdateLight(sf::Vector2f playerPosition)
{
	for (sf::Sprite& sprite : _lightGrid)
	{
		float tileAlpha = 255.f;			// Tile alpha.
		float distance = 0.f;				// The distance between player and tile.

		// Calculate distance between tile and player.
		distance = DistanceBetweenPoints(sprite.getPosition(), playerPosition);

		// Calculate tile transparency.
		if (distance < 200.f)
		{
			tileAlpha = 0.f;
		}
		else if (distance < 250.f)
		{
			tileAlpha = (51.f * (distance - 200.f)) / 10.f;
		}

		// Get all torches from the level.
		auto torches = _level.GetTorches();

		// If there are torches.
		if (!torches->empty())
		{
			// Update the light surrounding each torch.
			for (std::shared_ptr<Torch> torch : *torches)
			{
				// If the light tile is within range of the torch.
				distance = DistanceBetweenPoints(sprite.getPosition(), torch->GetPosition());
				if (distance < 100.f)
				{
					// Edit its alpha.
					tileAlpha -= (tileAlpha - ((tileAlpha / 100.f) * distance)) * torch->GetBrightness();
				}
			}

			// Ensure alpha does not go negative.
			if (tileAlpha < 0)
			{
				tileAlpha = 0;
			}
		}

		// Set the sprite transparency.
		sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(tileAlpha)));
	}
}

// Updates all items in the level.
void World::UpdateItems(sf::Vector2f playerPosition)
{
	// Update all items.
	auto itemIterator = _items.begin();
	while (itemIterator != _items.end())
	{
		// Get the item from the iterator.
		Item& item = **itemIterator;

		// Players gets the item (Poor distance)
		if (DistanceBetweenPoints(item.GetPosition(), playerPosition) < 40.f)
		{
			// Check what type of object it was.
			switch (item.GetType())
			{
			case ITEM::GOLD:
			{
				// Get the amount of gold.
				Gold gold = dynamic_cast<Gold&>(item);
				int goldvalue = gold.GetGoldValue();
				// Add to the gold total.
				_goldTotal += goldvalue;
				//Play gold collect sound effect
				gold.GetComponent<Audio>()->Play();
				
				if (_activeGoal)
					_goldGoal -= goldvalue;
			}

			break;

			case ITEM::GEM:
			{
				// Get the score of the gem.
				Gem g = dynamic_cast<Gem&>(item);
				int scoreValue = g.GetScoreValue();
				
				// Add to the score total
				_scoreTotal += scoreValue;			
				g.GetComponent<Audio>()->Play();
				

				if (_activeGoal)
					--_gemGoal;

			}
			break;

			case ITEM::KEY:
			{
				Key k = dynamic_cast<Key&>(item);
				// Unlock the door.
				_level.UnlockDoor();

				// Set the key as collected.
				_keyUiSprite->setColor(sf::Color::White);
				k.GetComponent<Audio>()->Play();
			}
			break;

			case ITEM::POTION:
			{
				// Cast to position and get type.
				Potion& potion = dynamic_cast<Potion&>(item);
				POTION potionType = potion.GetPotionType();

				switch (potionType)
				{
				case POTION::ATTACK:
					_player.SetAttack(_player.GetAttack() + potion.GetAttack());
					break;

				case POTION::DEFENSE:
					_player.SetDefense(_player.GetDefense() + potion.GetDefense());
					break;

				case POTION::STRENGTH:
					_player.SetStrength(_player.GetStrength() + potion.GetStrength());
					break;

				case POTION::DEXTERITY:
					_player.SetDexterity(_player.GetDexterity() + potion.GetDexterity());
					break;

				case POTION::STAMINA:
					_player.SetStamina(_player.GetStamina() + potion.GetStamina());
					break;
				}
			}
			break;

			case ITEM::HEART:
				// Cast to heart and get health.
				Heart& heart = dynamic_cast<Heart&>(item);

				_player.SetHealth(_player.GetHealth() + heart.GetHealth());
			}

			// Finally, delete the object.
			itemIterator = _items.erase(itemIterator);
		}
		else
		{
			// Increment iterator.
			++itemIterator;
		}
	}
}



// Updates all enemies in the level.
void World::UpdateEnemies(sf::Vector2f playerPosition, float timeDelta)
{
	// Store player tile.
	Tile* playerTile = _level.GetTile(_player.GetPosition());

	auto enemyIterator = _enemies.begin();
	while (enemyIterator != _enemies.end())
	{
		// Create a bool so we can check if an enemy was deleted.
		bool enemyWasDeleted = false;

		// Get the enemy object from the iterator.
		Enemy& enemy = **enemyIterator;

		// Get the tile that the enemy is on.
		Tile* enemyTile = _level.GetTile(enemy.GetPosition());

		// Check for collisions with projectiles.
		auto projectilesIterator = _playerProjectiles.begin();
		while (projectilesIterator != _playerProjectiles.end())
		{
			// Get the projectile object from the iterator.
			Projectile& projectile = **projectilesIterator;

			// If the enemy and projectile occupy the same tile they have collided.
			if (enemyTile == _level.GetTile(projectile.GetPosition()))
			{
				// Delete the projectile.
				projectilesIterator = _playerProjectiles.erase(projectilesIterator);

				// Damage the enemy.
				enemy.Damage(25);
				


				/*
				* we check if the enemy is dead
				* if is dead we need to add LOOT to the corpse, animations, bags...
				*
				*/

				// If the enemy is dead remove it.
				if (enemy.IsDead())
				{
					// Get the enemy position.
					sf::Vector2f position = enemy.GetPosition();

					// Spawn loot.

	
					
					for (int i = 0; i < 3; i++)
					{

						position.x += std::rand() % 31 - 15;
						position.y += std::rand() % 31 - 15;
						std::unique_ptr<Item> item;

						switch (std::rand() % 2)
						{
						case 0: // Spawn gold.
							//item = std::make_unique<Gold>();
							SpawnItem(ITEM::GOLD, position);
							break;

						case 1: // Spawn gem.
							//item = std::make_unique<Gem>();
							SpawnItem(ITEM::GEM, position);
							break;
						}
					}

					if ((std::rand() % 5) == 0)			// 1 in 5 change of spawning health.
					{
						position.x += std::rand() % 31 - 15;
						position.y += std::rand() % 31 - 15;
						SpawnItem(ITEM::HEART, position);
					}
					// 1 in 5 change of spawning potion.
					else if ((std::rand() % 5) == 1)
					{
						
						position.x += std::rand() % 31 - 15;
						position.y += std::rand() % 31 - 15;
						SpawnItem(ITEM::POTION, position);
					}

					//Play enemy kill sound.
					//enemy.GetComponent<Audio>()->Play();
					//PlaySound(_enemyDieSound, position);

					// Delete enemy.
					enemyIterator = _enemies.erase(enemyIterator);
					enemyWasDeleted = true;

					// Since the enemy is dead we no longer need to check projectiles.
					projectilesIterator = _playerProjectiles.end();

					if (_activeGoal)
						--_killGoal;
				}
			}
			else
			{
				// Move to the next projectile.
				++projectilesIterator;
			}
		}

		// If the enemy was not deleted, update it and increment the iterator.
		if (!enemyWasDeleted)
		{
			enemy.Update(timeDelta);
			++enemyIterator;
		}

		// Check for collision with player.
		if (enemyTile == playerTile)
		{
			if (_player.CanTakeDamage())
			{
				_player.Damage(10);
			}
		}
	}
}


// Updates all projectiles in the level.
void World::UpdateProjectiles(float timeDelta)
{
	auto projectileIterator = _playerProjectiles.begin();
	while (projectileIterator != _playerProjectiles.end())
	{
		// Get the projectile object from the iterator.
		Projectile& projectile = **projectileIterator;

		// Get the tile that the projectile is on.
		TILE projectileTileType = _level.GetTile(projectile.GetPosition())->type;

		// If the tile the projectile is on is not floor, delete it.
		if ((projectileTileType != TILE::FLOOR) && (projectileTileType != TILE::FLOOR_ALT))
		{
			projectileIterator = _playerProjectiles.erase(projectileIterator);
		}
		else
		{
			// Update the projectile and move to the next one.
			projectile.Update(timeDelta);
			++projectileIterator;
		}
	}
}

// Generates a random level goal
void World::GenerateLevelGoal()
{
	std::ostringstream ss;

	//reset goals
	_killGoal = 0;
	_goldGoal = 0;
	_gemGoal = 0;

	int goalType = rand() % 3;
	switch (goalType)
	{
	case 0:     // Kill X Enemies
		_killGoal = rand() % 6 + 5;
		// Create the string describing the goal.
		ss << "Current Goal: Kill " << _killGoal << " enemies" << "!" << std::endl;
		break;
	case 1:    // Collect X Gold
		_goldGoal = rand() % 51 + 50;
		ss << "Current Goal: Collect " << _goldGoal << " gold" << "!" << std::endl;
		break;
	case 2:    // Collect X Gems
		_gemGoal = rand() % 6 + 5;

		// Create the string describing the goal.
		ss << "Current Goal: Collect " << _gemGoal << " gems" << "!" << std::endl;

		break;
	}

	_goalString = ss.str();

	_activeGoal = true;
}



// Calculates the distance between two given points.
float World::DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2)
{
	return (abs(sqrt(((position1.x - position2.x) * (position1.x - position2.x)) + ((position1.y - position2.y) * (position1.y - position2.y)))));
}

// Draw the given string at the given position.
void World::DrawString(std::string text, sf::Vector2f position, unsigned int size)
{
	// Clear the old data.
	_strStream.str(std::string());
	_string.clear();

	/* CONSOLE*/
	/*
	sf::RectangleShape rectangle;
	int y = _screenSize.y/4;
	rectangle.setSize({(float)_screenSize.x/4, (float)y});
	rectangle.setPosition(0, _window.getSize().y-y);
	rectangle.setFillColor(sf::Color(0, 0, 0, 100));
	_window.draw(rectangle);
	*/

	_strStream << text;
	_string = _strStream.str();

	_text.setString(_string);
	_text.setFont(_font);
	_text.setCharacterSize(size);
	_text.setPosition(position.x - (_text.getLocalBounds().width / 2.f), position.y - (_text.getLocalBounds().height / 2.f));

	_window.draw(_text);
	
}

// Draw the current game scene.
void World::Draw(float timeDelta)
{
	// Clear the screen.
	_window.clear(sf::Color(3, 3, 3, 225));		// Gray

	// Check what state the game is in.
	switch (_gameState)
	{
	case GAME_STATE::MAIN_MENU:
		// Draw main menu ...
		break;

	case GAME_STATE::PLAYING:
	{

		/* DEBUG MODE, commnet setView to get a general view of the map*/
		// Set the main game view.
		// mWorld.draw()->setView(NORMAL)
		_window.setView(_views[static_cast<int>(VIEW::MAIN)]);


		/* Draw Entities && lights*/
		/****************************************************************************************************************************/
		/****************************************************************************************************************************/
		// Draw the level.
		_level.Draw(_window, timeDelta);

		// Draw all objects.
		for (const auto& item : _items)
			item->Draw(_window, timeDelta);	
		// Draw all enemies.
		for (const auto& enemy : _enemies)
			enemy->Draw(_window, timeDelta);
		// Draw all projectiles
		for (const auto& proj : _playerProjectiles)
			_window.draw(proj->GetSprite());
		// Draw the player.
		_player.Draw(_window, timeDelta);
		// Draw level light.
		for (const sf::Sprite& sprite : _lightGrid)
			_window.draw(sprite);	
		/****************************************************************************************************************************/
		/****************************************************************************************************************************/

		//mWindow.getDefaultView() --> la de la interfaz
		// Switch to UI view.
		_window.setView(_views[static_cast<int>(VIEW::UI)]);
		/* GUI*/
		/****************************************************************************************************************************/
		/****************************************************************************************************************************/

		// Draw player aim.
		_window.draw(_player.GetAimSprite());
		ImGui::Render();

		
		// Draw the level goal if active.
		if (_activeGoal)
		{
			DrawString(_goalString, sf::Vector2f(static_cast<float>(_window.getSize().x / 2), static_cast<float>(_window.getSize().y - 75)), 30);
			
		}

		// Draw player stats.
		DrawString(std::to_string(_player.GetAttack()), sf::Vector2f(_screenCenter.x - 210.f, _screenSize.y - 30.f), 25);
		DrawString(std::to_string(_player.GetDefense()), sf::Vector2f(_screenCenter.x - 90.f, _screenSize.y - 30.f), 25);
		DrawString(std::to_string(_player.GetStrength()), sf::Vector2f(_screenCenter.x + 30.f, _screenSize.y - 30.f), 25);
		DrawString(std::to_string(_player.GetDexterity()), sf::Vector2f(_screenCenter.x + 150.f, _screenSize.y - 30.f), 25);
		DrawString(std::to_string(_player.GetStamina()), sf::Vector2f(_screenCenter.x + 270.f, _screenSize.y - 30.f), 25);

		// Draw player score.
		std::string scoreString;

		if (_scoreTotal > 99999)
		{
			scoreString = std::to_string(_scoreTotal);
		}
		else if (_scoreTotal > 9999)
		{
			scoreString = "0" + std::to_string(_scoreTotal);
		}
		else if (_scoreTotal > 999)
		{
			scoreString = "00" + std::to_string(_scoreTotal);
		}
		else if (_scoreTotal > 99)
		{
			scoreString = "000" + std::to_string(_scoreTotal);
		}
		else if (_scoreTotal > 9)
		{
			scoreString = "0000" + std::to_string(_scoreTotal);
		}
		else
		{
			scoreString = "00000" + std::to_string(_scoreTotal);
		}

		DrawString(scoreString, sf::Vector2f(_screenCenter.x - 120.f, 40.f), 40);

		// Draw gold total.
		std::string goldString;

		if (_goldTotal > 99999)
		{
			goldString = std::to_string(_goldTotal);
		}
		else if (_goldTotal > 9999)
		{
			goldString = "0" + std::to_string(_goldTotal);
		}
		else if (_goldTotal > 999)
		{
			goldString = "00" + std::to_string(_goldTotal);
		}
		else if (_goldTotal > 99)
		{
			goldString = "000" + std::to_string(_goldTotal);
		}
		else if (_goldTotal > 9)
		{
			goldString = "0000" + std::to_string(_goldTotal);
		}
		else
		{
			goldString = "00000" + std::to_string(_goldTotal);
		}

		DrawString(goldString, sf::Vector2f(_screenCenter.x + 220.f, 40.f), 40);

		// Draw rest of the UI.
		for (const auto& sprite : _uiSprites)
		{
			_window.draw(*sprite);
		}

		// Draw the current room and floor.
		DrawString("Floor " + std::to_string(_level.GetFloorNumber()), sf::Vector2f(_screenSize.x - 50, _screenSize.y - 300.f), 20);
		DrawString("Room " + std::to_string(_level.GetRoomNumber()), sf::Vector2f(_screenSize.x - 50, _screenSize.y - 275.f), 20);
		

		// Draw health and mana bars.
		_healthBarSprite->setTextureRect(sf::IntRect(0, 0, (213.f / _player.GetMaxHealth()) * _player.GetHealth(), 8));
		
		_window.draw(*_healthBarSprite);
		
		_manaBarSprite->setTextureRect(sf::IntRect(0, 0, (213.f / _player.GetMaxMana()) * _player.GetMana(), 8));
		_window.draw(*_manaBarSprite);
		
		//
	}
	break;

	case GAME_STATE::GAME_OVER:
		// Draw game over screen ...
		break;
	}

	
	// Present the back-buffer to the screen.
	_window.display();
	
}


//Choose a random, unused spawn location if not overriden.
void World::SpawnItem(ITEM itemType, sf::Vector2f position){

	std::unique_ptr<Item> item;
	int oIndex;

	/*
	* Checking if we have a valid position to spawn the item
	* 
	*/
	sf::Vector2f spawnLocation;
	if ((position.x >= 0.f) || (position.y >= 0.f))
		spawnLocation = position;
	else
		spawnLocation = _level.GetRandomSpawnLocation();


	switch (itemType) {
		case ITEM::POTION:
			item = std::make_unique<Potion>();
			break;
		case ITEM::GEM:
			item = std::make_unique<Gem>();
			break;
		case ITEM::GOLD:
			item = std::make_unique<Gold>();
			break;
		case ITEM::KEY:
			item = std::make_unique<Key>();
			break;
		case ITEM::HEART:
			item = std::make_unique<Heart>();
			break;
	}

	//Set the item position.
	item->SetPosition(spawnLocation);

	//add the item to the list of all items.
	_items.push_back(std::move(item));

}



void World::SpawnEnemy(ENEMY enemyType, sf::Vector2f position)
{
	/*Spawn location of enemy*/
	sf::Vector2f spawnLocation;

	if ((position.x >= 0.f) || (position.y >= 0.f))
		spawnLocation = position;
	else
		spawnLocation = _level.GetRandomSpawnLocation();

	/*create the enemy*/
	std::unique_ptr<Enemy> enemy;

	switch (enemyType) {
		case ENEMY::HUMANOID:
			enemy = std::make_unique<Humanoid>();
			break;
		case ENEMY::SLIME:
			enemy = std::make_unique<Slime>();
			break;
	}

		enemy->SetPosition(spawnLocation);
		_enemies.push_back(std::move(enemy));
}


void World::SpawnRandomTiles(TILE tileType, int count)
{

	//Loop the number of tiles we need.
	for (int i = 0; i < count; i++)
	{
		int columnIndex(0), rowIndex(0);

		while (!_level.IsFloor(columnIndex, rowIndex)) {
			columnIndex = std::rand() % GRID_WIDTH;
			rowIndex = std::rand() %GRID_HEIGHT;
		}

		_level.SetTile(columnIndex, rowIndex, tileType);
	}
}


