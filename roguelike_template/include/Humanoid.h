#ifndef HUMANOID_H
#define HUMANOID_H

#include "Enemy.h"

class Humanoid : public Enemy
{
public:

	/**
	 * Default constructor
	 */
	Humanoid();

	/**
	* Overrides the update event of Enemy.
	* @param timeDelta The time that has elapsed since the last update.
	*/
	void Update(float timeDelta) override;


private:

	/**
	* An array of modified textures.
	*/
	sf::Texture m_textures[static_cast<int>(ANIMATION_STATE::COUNT)];


	/**
	* Generates random armor for the humanoid.
	*/
	void GenerateArmor();


};
#endif