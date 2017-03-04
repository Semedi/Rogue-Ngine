#ifndef LEVEL_H
#define LEVEL_H

#include <Torch.h>
#include <Util.h>
#include <SpriteNode.h>



// Constants for the game grid size.
static int const GRID_WIDTH = 19;
static int const GRID_HEIGHT = 19;

// The width and height of each tile in pixels.
static int const TILE_SIZE = 50;

// The level tile type.
struct Tile : SpriteNode  {

	TILE type;							// The type of tile this is.
	int columnIndex;					// The column index of the tile.
	int rowIndex;						// The row index of the tile.

	sf::Sprite sprite;					// The tile sprite.
	int H;								// Heuristic / movement cost to goal.
	int G;								// Movement cost. (Total of entire path)
	int F;								// Estimated cost for full path. (G + H)
	Tile* parentNode;					// Node to reach this node.

};

class Level
{
public:

	typedef std::unique_ptr<Tile> Ptr;
	/**
	 * Default constructor.
	 */
	Level();

	/**
	 * Constructor.
	 * A renderWindow is needed in order for the level to calculate its position.
	 * @param window The game window.
	 */
	Level(sf::RenderWindow& window);

	void init(sf::RenderWindow& window);
	/**
	 * Returns true if the given tile index is solid.
	 * @param columnIndex The tile's column index.
	 * @param rowIndex The tile's row index.
	 * @return True if the given tile is solid.
	 */
	bool IsSolid(int columnIndex, int rowIndex);

	/**
	 * Sets the index of a given tile in the 2D game grid.
	 * This also changes the tile sprite, and is how tiles should be changed and set manually.
	 * @param columnIndex The tile's column index.
	 * @param rowIndex The tile's row index.
	 * @param index The new index of the tile.
	 */
	void SetTile(int columnIndex, int rowIndex, TILE tileType);

	/**
	 * Draws the level grid to the provided render window.
	 * @param window The render window to draw the level to.
	 * @param timeDelta The time that has elapsed since the last update.
	 */
	void Draw(sf::RenderWindow &window, float timeDelta);

	/**
	 * Gets the index of the given tile.
	 * @param columnIndex The column index of the tile to check.
	 * @param rowIndex The row index of the tile to check.
	 * @return The index of the given tile.
	 */
	TILE GetTileType(int columnIndex, int rowIndex) const;

	/**
	 * Loads a level from a text file.
	 * @param fileName The path to the level file to load.
	 * return true if the level loaded succesfully.
	 */
	bool LoadLevelFromFile(std::string fileName);

	/**
	* Generates a random level.
	*/
	void GenerateLevel();

	/**
	 * Gets the tile at the given position.
	 * @param position The coordinates of the position to check.
	 * @return A pointer to the tile at the given location.
	 */
	Tile* GetTile(sf::Vector2f position);

	/**
	* Gets the tile at the given position in the level array.
	* @param columnIndex The column that the tile is in.
	* @param rowIndex The row that the tile is in.
	* @return A pointer to the tile if valid.
	*/
	Tile* GetTile(int columnIndex, int rowIndex);

	/**
	 * Gets the position of the level grid relative to the window.
	 * @return The position of the top-left of the level grid.
	 */
	sf::Vector2f GetPosition() const;

	/**
	 * Gets a vector of all torches in the level.
	 * @return A vector of shared_ptrs containing all torches in the level.
	 */
	std::vector<std::shared_ptr<Torch>>* GetTorches();

	/**
	 * Checks if a given tile is valid.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return True if the tile is valid.
	 */
	bool TileIsValid(int columnIndex, int rowIndex);


	/**
	* Sets the overlay color of the level tiles.
	* @param tileColor The new tile overlay color.
	*/
	void SetColor(sf::Color tileColor);


	/**
	 * Gets the current floor number.
	 * @return The current floor.
	 */
	int GetFloorNumber() const;

	/**
	 * Gets the current room number.
	 * @return The current room.
	 */
	int GetRoomNumber() const;

	/**
	 * Gets the size of the level in terms of tiles.
	 * @return The size of the level grid.
	 */
	sf::Vector2i GetSize() const;

	/**
	 * Spawns a given number of torches in the level.
	 * @param torchCount The number of torches to create.
	 */
	void SpawnTorches(int torchCount);

	/**
	 * Unlocks the door in the level.
	 */
	void UnlockDoor();

	/**
	 * Return true if the given tile is a floor tile.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return True if the given tile is a floor tile.
	 */
	bool IsFloor(int columnIndex, int rowIndex);

	/**
	* Return true if the given tile is a floor tile.
	* @param tile The tile to check
	* @return True if the given tile is a floor tile.
	*/
	bool IsFloor(const Tile& tile);

	/**
	 * Returns the size of the tiles in the level.
	 * @return The size of the tiles in the level.
	 */
	int GetTileSize() const;

	/**
	* Adds a tile to the level.
	* These tiles are essentially sprites with a unique index. Once added, they can be loaded via the LoadLevelFromFile() function by including its index in the level data.
	* @param fileName The path to the sprite resource, relative to the project directory.
	* @param tileType The type of tile that is being added.
	* @return The index of the tile. This is used when building levels.
	*/
	int AddTile(std::string fileName, TILE tileType);


	/* METODOS A�ADIDOS:*/

	/*
	*Returns the position of a tile on the screen.
	*/
	sf::Vector2f GetActualTileLocation(int columnIndex, int rowIndex);

	/*Returns a valid spawn location*/
	sf::Vector2f GetRandomSpawnLocation();

	public:
	/**
	* Resets the A* data of all tiles.
	*/
	void ResetNodes();

	std::unique_ptr<SpriteNode> GetTileMap();
	// Returns spawn location
	sf::Vector2f SpawnLocation()
	{
		return _spawnLocation;
	}


private:

	/**
	 * Checks if a given tile is a wall block.
	 * @param columnIndex The column that the tile is in.
	 * @param rowIndex The column that the row is in.
	 * @return True if the given tile is a wall tile.
	 */
	bool IsWall(int columnIndex, int rowIndex);

	/*
	* Create a path between two nodes
	*/
	void CreatePath(int columnIndex, int rowIndex);

	/*
	*  Adds a given number 4 rooms (open space)
	*/
	void CreateRooms(int roomCount);

	/* Calculate the correct texture 4 the tile */
	void CalculateTextures();

	/* Generate entry/exit points */
	void GenerateEntryExit();

	/**/
	void LoadTiles();

	

private:
	/**
	 * A 2D array that describes the level data.
	 * The type is Tile, which holds a sprite and an index.
	 */	
	Tile* __grid[GRID_HEIGHT][GRID_HEIGHT];

	std::unique_ptr<SpriteNode> _tileMap;
	

	std::vector<sf::Sprite> _tileSprites; //A vector off all the sprites in the level.

	/**
	 * The position of the level relative to the window.
	 * This is to the top-left of the level grid.
	 */
	sf::Vector2i _origin;


	int _floorNumber; //The floor number that the player is currently on.
	int _roomNumber; //The room number that the player is currently in.
	int _roomLayout[3][10]; //A 2D array that contains the room layout for the current floor.

	int _textureIDs[static_cast<int>(TILE::COUNT)]; //An array containing all texture IDs of the level tiles.

	sf::Vector2i _doorTileIndices; //The indices of the tile containing the levels door.
	std::vector<std::shared_ptr<Torch>> _torches; //A vector of all tiles in the level.
	sf::Vector2f _spawnLocation; //The spawn location for the current level

	
};
#endif
