#ifndef UTIL_H
#define UTIL_H


namespace Category
{
	enum Type
	{
		None	= 0,
		Scene	= 1 << 0,
		Player	= 1 << 1,
		Npc		= 1 << 2,
		Enemy	= 1 << 3
	};
}

// Game states.
enum class GAME_STATE {
	MAIN_MENU,
	PLAYING,
	GAME_OVER
};

enum class Layer
{
	Background,
	Mid,
	Top,
	COUNT
};




//Player traits.
enum class PLAYER_TRAIT {
	ATTACK,
	DEFENSE,
	STRENGTH,
	DEXTERY,
	STAMINA,
	COUNT
};

//Player Classes
enum class PLAYER_CLASS {
	WARRIOR,
	MAGE,
	ARCHER,
	THIEF,
	COUNT
};

// Potions.
enum class POTION {
	ATTACK,
	DEFENSE,
	STRENGTH,
	DEXTERITY,
	STAMINA,
	COUNT
};

// Spawnable items.
enum class ITEM {
	GEM,
	GOLD,
	HEART,
	POTION,
	KEY,
	COUNT
};

// Enemy types.
enum class ENEMY {
	SLIME,
	HUMANOID,
	COUNT
};

enum class HUMANOID {
	GOBLIN,
	SKELETON,
	COUNT
};


// Animation states.
enum class ANIMATION_STATE {
	WALK_UP,
	WALK_DOWN,
	WALK_RIGHT,
	WALK_LEFT,
	IDLE_UP,
	IDLE_DOWN,
	IDLE_RIGHT,
	IDLE_LEFT,
	COUNT
};

// Tiles.
enum class TILE {
	WALL_SINGLE,
	WALL_TOP_END,
	WALL_SIDE_RIGHT_END,
	WALL_BOTTOM_LEFT,
	WALL_BOTTOM_END,
	WALL_SIDE,
	WALL_TOP_LEFT,
	WALL_SIDE_LEFT_T,
	WALL_SIDE_LEFT_END,
	WALL_BOTTOM_RIGHT,
	WALL_TOP,
	WALL_BOTTOM_T,
	WALL_TOP_RIGHT,
	WALL_SIDE_RIGHT_T,
	WALL_TOP_T,
	WALL_INTERSECTION,
	WALL_DOOR_LOCKED,
	WALL_DOOR_UNLOCKED,
	WALL_ENTRANCE,
	FLOOR,
	FLOOR_ALT,
	CRATE,
	EMPTY,
	COUNT
};

enum class COLOR {
	BLACK,
	WHITE,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	CYAN,
	TRANSPARENT,
	COUNT
};


// Music tracks.
enum class MUSIC_TRACK {
	ALT_1,
	ALT_2,
	ALT_3,
	ALT_4,
	ALT_5,
	COUNT
};



// Game views.
enum class VIEW {
	MAIN,
	UI,
	COUNT
};
#endif