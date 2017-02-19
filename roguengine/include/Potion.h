#ifndef POTION_H
#define POTION_H

#include <Item.h>

class Potion : public Item
{
public:
	/**
	* Default constructor.
	*/
	Potion();

	/**
	* Gets the potion type.
	* @return The potion type.
	*/
	POTION GetPotionType() const;

	/**
	 * Gets the attack value of the potion.
	 * @return The attack value the potion gives.
	 */
	int GetAttack() const;

	/**
	 * Gets the defense value of the potion.
	 * @return The defense value the potion gives.
	 */
	int GetDefense() const;

	/**
	 * Gets the strength value of the potion.
	 * @return The strength value the potion gives.
	 */
	int GetStrength() const;

	/**
	 * Gets the dexterity value of the potion.
	 * @return The dexterity value the potion gives.
	 */
	int GetDexterity() const;

	/**
	 * Gets the stamina value of the potion.
	 * @return The stamina value the potion gives.
	 */
	int GetStamina() const;

private:

	POTION _potionType; //The potion type.

	int _attack; //The attack value of the potion.
	int _defense; //The defense value of the potion.
	int _strength; //The strength value of the potion.
	int _dexterity; //The dexterity value of the potion.
	int _stamina; //The stamina value of the potion.
};
#endif