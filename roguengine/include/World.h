#ifndef WORLD_H
#define WORLD_H


#include <Player.h>
#include <Item.h>
#include <Level.h>
#include <Gold.h>
#include <Key.h>
#include <Gem.h>
#include <Potion.h>
#include <Heart.h>
#include <Slime.h>
#include <Humanoid.h>
#include <SceneNode.h>
#include <array>



static float const FPS = 60.0;						// Constant for fixed time - step loop. We'll lock it at 60fps.
static float const MS_PER_STEP = 1.0f / FPS;		// Roughly (0.017) @ 60fps.

static int const MAX_ITEM_SPAWN_COUNT = 50;
static int const MAX_ENEMY_SPAWN_COUNT = 20;

class World
{
public:

	/**
	 * Constructor.
	 * @param window A pointer to the main render window.
	 */
	World(sf::RenderWindow* window);
	
	/**
	 * Initializes the game object by initializing all objects the main game uses.
	 * @return True if the game was initialized successfully.
	 */
	void Init();

	/**
	 * Returns true if the game is currently running.
	 * @return True if the game is running.
	 */
	bool IsRunning();

	/**
	 * The main update loop. This loop in turns calls the update loops of all game objects.
	 * @param timeDelta The time, in MS, since the last update call.
	 */
	void Update(sf::Time dt);

	/**
	 * Draws all game objects to screen.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	void Draw(float timeDelta);

	
	/* SPAWN FUNCTIONS */
	void SpawnItem(ITEM itemType, sf::Vector2f position = { -1.f, -1.f });
	void SpawnEnemy(ENEMY enemyType, sf::Vector2f position = { -1.f, -1.f });
	void SpawnRandomTiles(TILE tileType, int count);

private:

	/**
	* Plays the given sound effect, with randomized parameters./
	*/
	void PlaySound(sf::Sound& sound, sf::Vector2f position = { 0.f, 0.f });

	/**
	 * Populates the current game room with items and enemies.
	 */
	void PopulateLevel();


	/**
	* Generates a new level.
	*/
	void GenerateLevel();


	/**
	 * Loads all sprites needed for the UI.
	 */
	void LoadUI();

	/**
	 * Calculates the distance between two points
	 * @param position1 The position of the first point.
	 * @param position2 The position of the second item.
	 * @return The distance between the two points.
	 */
	float DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2);

	/**
	 * Draws text at a given location on the screen.
	 * @param text The string you wish to draw.
	 * @param position The top-left position of the string.
	 * @param size (Optional) The font-size to use. Default value is 10.
	 */
	void DrawString(std::string text, sf::Vector2f position, unsigned int size = 10);

	/**
	 * Constructs the grid of sprites that are used to draw the game light system.
	 */
	void ConstructLightGrid();

	/**
	 * Updates the level light.
	 * @param playerPosition The position of the players within the level.
	 */
	void UpdateLight(sf::Vector2f playerPosition);

	/**
	 * Updates all items in the level.
	 * @param playerPosition The position of the players within the level.
	 */
	void UpdateItems(sf::Vector2f playerPosition);

	/**
	 * Updates all enemies in the level.
	 * @param playerPosition The position of the players within the level.
	 * @param timeDelta The amount of time that has passed since the last update.
	 */
	void UpdateEnemies(sf::Vector2f playerPosition, float timeDelta);

	/**
	 * Updates all projectiles in the level.
	 * @param timeDetla The amount of time that has passed since the last update.
	 */
	void UpdateProjectiles(float timeDelta);


	/* Generates a lavel goal*/
	void GenerateLevelGoal();

	void processInput();
	void Build();


private:

	enum Layer
	{
		Background,
		Air,
		Top,
		LayerCount
	};

private:

	/* MAIN GRAPHICS*/
	sf::RenderWindow& _window;						//The main application window.
	sf::View _views[static_cast<int>(VIEW::COUNT)]; //An array of the different views the game needs.
	sf::Clock _stepCLK;								//Used in the main game time step.
	sf::Vector2u _screenSize;						//The size of the screen and window.
	sf::Vector2f _screenCenter;						//The center of the screen.


	// AUX
	bool _levelWasGenerated; //A boolean denoting if a new level was generated.
	bool _isRunning;		//A bool that tracks the running state of the game. It's used in the main loop.

	
	std::vector<std::unique_ptr<Item>> _items; //A vector that holds all items within the level.
	std::vector<std::unique_ptr<Enemy>> _enemies; //A vector that holds all the enemies within the level.
	
	// new
	SceneNode _Scene;
	std::array<SceneNode*, LayerCount> _Layers;
	


	/*GAMEPLAY*/
	Level _level; //The main level object. All data and functionally regarding the level lives in this class/object.
	Player _player; //The main player object. Only one instance of this object should be created at any one time.
	Tile* _playerPrevTile; //Player's prev tile



	//VISUAL EFFECTS
	std::vector<sf::Sprite> _lightGrid; //A vector containing all sprites that make up the lighting grid.


	/********************************************************
	* GUI
	*********************************************************/

	sf::Font _font;					//The default font to be used when drawing text.
	std::ostringstream _strStream;	//String stream used by the DrawText() function.
	std::string _string;			//String used by the DrawText() function.
	sf::Text _text;					//Text used by the DrawText() function.


	int _scoreTotal; //The current game score.
	int _goldTotal; //The amount of gold that the player currently has.


	std::shared_ptr<sf::Sprite> _playerUiSprite; //The sprite that shows the player class in the UI.
	std::shared_ptr<sf::Sprite> _coinUiSprite; //The sprite used to show how many coins the player has.
	std::shared_ptr<sf::Sprite> _gemUiSprite; //The sprite used to show how much score the player has.
	std::shared_ptr<sf::Sprite> _keyUiSprite; //Key ui sprite.

	std::shared_ptr<sf::Sprite> _attackStatSprite; //The sprite for the players attack stat.
	int _attackStatTextureIDs[2]; //The texture IDs for the attack stat textures

	std::shared_ptr<sf::Sprite> _defenseStatSprite; //The sprite for the players defense stat.
	int _defenseStatTextureIDs[2]; //The texture IDs for the defense stat textures.


	std::shared_ptr<sf::Sprite> _strengthStatSprite; //The sprite for the players strength stat.
	int _strengthStatTextureIDs[2]; //The texture IDs for the strength stat textures.


	std::shared_ptr<sf::Sprite> _dexterityStatSprite; //The sprite for the players dexterity stat.
	int _dexterityStatTextureIDs[2]; //The texture IDs for the dexterity stat textures.


	std::shared_ptr<sf::Sprite> _staminaStatSprite; //The sprite for the players stamina stat.
	int _staminaStatTextureIDs[2]; //The texture IDs for the stamina stat textures.
	 

	std::vector<std::unique_ptr<Projectile>> _playerProjectiles; //A vector of all the player's projectiles.
	int _projectileTextureID; //The ID of the player's projectile texture.



	std::shared_ptr<sf::Sprite> _healthBarSprite;			//Sprite for the health bar.
	std::shared_ptr<sf::Sprite> _healthBarOutlineSprite;	//Sprite for the health bar outline.
	std::shared_ptr<sf::Sprite> _manaBarSprite;				//Sprite for the mana bar.
	std::shared_ptr<sf::Sprite> _manaBarOutlineSprite;		//Sprite for the mana bar outline.
	std::vector<std::shared_ptr<sf::Sprite>> _uiSprites;	//A vector of all ui sprites.

	/****************************************************
	*
	*    MUSIC PART
	*****************************************************/
	sf::Music _music;			//Main Music
	sf::Sound _fireSound;		//Torch sound.
	sf::Sound _enemyDieSound;	//Enemy die sound.



	/************************
	*
	*GOAL VARIABLES
	************************/
	int _goldGoal;
	int _gemGoal;
	int _killGoal;
	sf::String _goalString;

	bool _activeGoal;





	
};
#endif

