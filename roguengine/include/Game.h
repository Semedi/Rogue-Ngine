#ifndef GAME_H
#define GAME_H

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

static float const FPS = 60.0;						// Constant for fixed time - step loop. We'll lock it at 60fps.
static float const MS_PER_STEP = 1.0f / FPS;		// Roughly (0.017) @ 60fps.

static int const MAX_ITEM_SPAWN_COUNT = 50;
static int const MAX_ENEMY_SPAWN_COUNT = 20;

class Game
{
public:
	/**
	 * Constructor.
	 * @param window A pointer to the main render window.
	 */
	Game(sf::RenderWindow* window);
	
	/**
	 * Initializes the game object by initializing all objects the main game uses.
	 * @return True if the game was initialized successfully.
	 */
	void Initialize();

	/**
	 * The main game loop. This loop in turn updates the game, and draws all objects to screen.
	 * It's also responsible for the game logic timing.
	 */
	void Run();

	/**
	 * Returns true if the game is currently running.
	 * @return True if the game is running.
	 */
	bool IsRunning();

	/**
	 * The main update loop. This loop in turns calls the update loops of all game objects.
	 * @param timeDelta The time, in MS, since the last update call.
	 */
	void Update(float timeDelta);

	/**
	 * Draws all game objects to screen.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	void Draw(float timeDelta);

	
	/*CODIGO MIO: **************************************************************************/

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

private:
	/**
	 * The main application window.
	 */
	sf::RenderWindow& _window;

	/**
	 * An array of the different views the game needs.
	 */
	sf::View _views[static_cast<int>(VIEW::COUNT)];

	/**
	 * Used in the main game time step.
	 */
	sf::Clock _stepCLK;

	Tile* _playerPrevTile;

	/**
	 * The default font to be used when drawing text.
	 */
	sf::Font _font;

	/**
	 * The game state.
	 */
	GAME_STATE _gameState;

	/**
	 * A vector that holds all items within the level.
	 */
	std::vector<std::unique_ptr<Item>> _items;

	/**
	 * A vector that holds all the enemies within the level.
	 */
	std::vector<std::unique_ptr<Enemy>> _enemies;

	/**
	 * A bool that tracks the running state of the game. It's used in the main loop.
	 */
	bool _isRunning;

	/**
	 * The main level object. All data and functionally regarding the level lives in this class/object.
	 */
	Level _level;

	/**
	 * The main player object. Only one instance of this object should be created at any one time.
	 */
	Player _player;

	/**
	 * String stream used by the DrawText() function.
	 */
	std::ostringstream _strStream;

	/**
	 * String used by the DrawText() function.
	 */
	std::string _string;

	/**
	 * Text used by the DrawText() function.
	 */
	sf::Text _text;

	/**
	 * A vector containing all sprites that make up the lighting grid.
	 */
	std::vector<sf::Sprite> _lightGrid;

	/**
	 * The size of the screen and window.
	 */
	sf::Vector2u _screenSize;

	/**
	* The center of the screen.
	*/
	sf::Vector2f _screenCenter;

	/**
	 * The current game score.
	 */
	int _scoreTotal;

	/**
	* The amount of gold that the player currently has.
	*/
	int _goldTotal;

	/**
	 * The sprite that shows the player class in the UI.
	 */
	std::shared_ptr<sf::Sprite> _playerUiSprite;

	/**
	 * The sprite used to show how many coins the player has.
	 */
	std::shared_ptr<sf::Sprite> _coinUiSprite;

	/**
	* The sprite used to show how much score the player has.
	*/
	std::shared_ptr<sf::Sprite> _gemUiSprite;

	/**
	 * Key ui sprite.
	 */
	std::shared_ptr<sf::Sprite> _keyUiSprite;

	/**
	 * The sprite for the players attack stat.
	 */
	std::shared_ptr<sf::Sprite> _attackStatSprite;

	/**
	 * The texture IDs for the attack stat textures.
	 */
	int _attackStatTextureIDs[2];

	/**
	* The sprite for the players defense stat.
	*/
	std::shared_ptr<sf::Sprite> _defenseStatSprite;

	/**
	* The texture IDs for the defense stat textures.
	*/
	int _defenseStatTextureIDs[2];

	/**
	* The sprite for the players strength stat.
	*/
	std::shared_ptr<sf::Sprite> _strengthStatSprite;

	/**
	* The texture IDs for the strength stat textures.
	*/
	int _strengthStatTextureIDs[2];

	/**
	* The sprite for the players dexterity stat.
	*/
	std::shared_ptr<sf::Sprite> _dexterityStatSprite;

	/**
	* The texture IDs for the dexterity stat textures.
	*/
	int _dexterityStatTextureIDs[2];

	/**
	* The sprite for the players stamina stat.
	*/
	std::shared_ptr<sf::Sprite> _staminaStatSprite;

	/**
	* The texture IDs for the stamina stat textures.
	*/
	int _staminaStatTextureIDs[2];

	/**
	 * A vector of all the player's projectiles.
	 */
	std::vector<std::unique_ptr<Projectile>> _playerProjectiles;

	/**
	 * The ID of the player's projectile texture.
	 */
	int _projectileTextureID;

	/**
	 * A boolean denoting if a new level was generated.
	 */
	bool _levelWasGenerated;

	/**
	 * Sprite for the health bar.
	 */
	std::shared_ptr<sf::Sprite> _healthBarSprite;

	/**
	* Sprite for the health bar outline.
	*/
	std::shared_ptr<sf::Sprite> _healthBarOutlineSprite;

	/**
	 * Sprite for the mana bar.
	 */
	std::shared_ptr<sf::Sprite> _manaBarSprite;

	/**
	* Sprite for the mana bar outline.
	*/
	std::shared_ptr<sf::Sprite> _manaBarOutlineSprite;

	/**
	 * A vector of all ui sprites.
	 */
	std::vector<std::shared_ptr<sf::Sprite>> _uiSprites;

	/****************************************************
	*
	*    MUSIC PART
	*****************************************************/

	sf::Music _music;
	/**
	* Torch sound.
	*/
	sf::Sound _fireSound;

	/**
	* Enemy die sound.
	*/
	sf::Sound _enemyDieSound;




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