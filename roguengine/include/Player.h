#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <Input.h>
#include <Level.h>
#include <Projectile.h>

class Player : public Entity
{
public:
	/**
	 * Default constructor.
	 */
	Player();

	/**
	 * Updates the player object.
	 * The main purpose of this function is to update the players position.
	 * @param timeDelta The time, in MS, since the last game tick.
	 * @param level A reference to the level object.
	 */
	void Update(float timeDelta, Level& level);

	/**
	* Gets the player's mana.
	* @return The player's mana.
	*/
	int GetMana() const;

	/**
	* Gets the player's max mana.
	* @return The player's max mana.
	*/
	int GetMaxMana() const;

	/**
	*Gets player current traits
	*@return the player two current traits
	*/
	PLAYER_TRAIT* GetTraits();

	int GetTraitCount();


	/**
	 * Set the player's health.
	 * @param healthValue The player's new health.
	 */
	void SetHealth(int healthValue);

	/**
	 * Set the player's mana level.
	 * @param mana The new mana value.
	 */
	void SetMana(int manaValue);

	/**
	 * Gets the player's aim sprite.
	 * return The player's aim sprite.
	 */
	sf::Sprite& GetAimSprite();

	/**
	 * Checks if the player is currently attacking.
	 * @return True if the player is attacking.
	 */
	bool IsAttacking();

	/**
	 * Checks if the player can take damage.
	 * @return True if the player can take damage.
	 */
	bool CanTakeDamage();

	/**
	 * Apply the given amount of damage to the player.
	 * @param damage The amount of damage to deal to the player.
	 */
	void Damage(int damage);


	static const int PLAYER_TRAIT_COUNT = 2;

	/*
	*
	* Getter of the class

	*/
	PLAYER_CLASS GetClass() const;


	/*
	*
	*Chooses random traits for the character
	*/

	void SetRandomTraits();

private:

	/**
	 * Checks if the given movement will result in a collision.
	 * @param movement The movement to check.
	 * @param level A reference to the level object.
	 * @return True if the given movement will result in a collision.
	 */
	bool CausesCollision(sf::Vector2f movement, Level& level);


	std::vector<std::string> BuildPlayer(PLAYER_CLASS c);

private:


	sf::Sprite _aimSprite; //The sprite for the player's aim cross hair.

	float _attackDelta; //The time since the player's last attack
	float _damageDt; //The time since the player last took damage.
	float _manaDt; //The time since the last mana regeneration.

	
	bool _attacking; //Is the player attacking.	
	bool _canTakeDamage; //Can the player take damage.

	int _statPoints; //number of stats points.

	PLAYER_CLASS _class; // player class reference to enu_class created in Util.
	PLAYER_TRAIT _traits[PLAYER_TRAIT_COUNT];

};
#endif
