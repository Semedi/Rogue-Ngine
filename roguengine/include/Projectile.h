#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Object.h>

class Projectile : public Object
{
public:
	/**
	 * Default constructor.
	 * @param texture The texture of the projectile.
	 * @param origin The location that the projectile should be created at.
	 * @param _screenCenter The center of the screen. Used to calculate direction.
	 * @param target The target location of the projectile.
	 */
	Projectile(sf::Texture& texture, sf::Vector2f origin, sf::Vector2f _screenCenter, sf::Vector2f target);

	/**
	 * Override of the update function.
	 * @param timeDelta The time in seconds since the last update.
	 */
	void Update(float timeDelta) override;

private:
	/**
	 * The velocity of the projectile.
	 */
	sf::Vector2f m_velocity;
};
#endif