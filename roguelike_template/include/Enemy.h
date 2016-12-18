#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Level.h"

class Enemy : public Entity
{
public:
	/**
	 * Default constructor.
	 */
	Enemy();

	/**
	 * Applies the given amount of damage to the enemy.
	 * @param damage The amount of damage to deal to the enemy.
	 */
	void Damage(int damage);

	/**
	 * Checks if the enemy has taken enough damage that they are now dead.
	 * @return True if the enemy is dead.
	 */
	bool IsDead();

	/**
	* Recalculates the target position of the enemy
	*/
	void UpdatePathfinding(Level &level, sf::Vector2f playerPosition);

	/**
	* Overrides the default Update function in Enemy
	*/
	void Update(float timeDelta) override;

	/**
	* Override the default draw function.
	*/
	void Draw(sf::RenderWindow& window, float timeDelta) override;

private:
	/**
	* The target positions of th enemy.
	*/
	std::vector<sf::Vector2f> m_targetPositions;

	/**
	* The current target of th enemy.
	*/
	sf::Vector2f m_currentTarget;


	//debug
	sf::Sprite m_pathSprite;

	//debug
	sf::Font m_font;
	sf::Text m_text;
};
#endif