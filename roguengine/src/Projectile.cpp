#include <PCH.h>
#include <Projectile.h>

// Default constructor.
Projectile::Projectile(sf::Texture& texture, sf::Vector2f origin, sf::Vector2f _screenCenter, sf::Vector2f target)
{
	// Create the sprite.
	SetSprite(texture, false);

	// Set the sprite position.
	_sprite.setPosition(origin);

	// Set the position.
	transform.position = origin;

	// Calculate the velocity of the object.
	_velocity = target - _screenCenter;

	float length = sqrt((_velocity.x * _velocity.x) + (_velocity.y * _velocity.y));
	_velocity.x /= length;
	_velocity.y /= length;
}

// Update the projectile.
void Projectile::Update(float timeDelta)
{
	// Update rotation.
	_sprite.setRotation(_sprite.getRotation() + (400.f * timeDelta));

	// Update position.
	_sprite.setPosition(_sprite.getPosition().x + (_velocity.x * (500 * timeDelta)), _sprite.getPosition().y + (_velocity.y * (500 * timeDelta)));
	transform.position = _sprite.getPosition();
}