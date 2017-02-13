#include <PCH.h>
#include <Projectile.h>

// Default constructor.
Projectile::Projectile(sf::Texture& texture, sf::Vector2f origin, sf::Vector2f _screenCenter, sf::Vector2f target)
{
	// Create the sprite.
	SetSprite(texture, false);

	// Set the sprite position.
	m_sprite.setPosition(origin);

	// Set the position.
	transform.position = origin;

	// Calculate the velocity of the object.
	m_velocity = target - _screenCenter;

	float length = sqrt((m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y));
	m_velocity.x /= length;
	m_velocity.y /= length;
}

// Update the projectile.
void Projectile::Update(float timeDelta)
{
	// Update rotation.
	m_sprite.setRotation(m_sprite.getRotation() + (400.f * timeDelta));

	// Update position.
	m_sprite.setPosition(m_sprite.getPosition().x + (m_velocity.x * (500 * timeDelta)), m_sprite.getPosition().y + (m_velocity.y * (500 * timeDelta)));
	transform.position = m_sprite.getPosition();
}