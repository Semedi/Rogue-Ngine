#include <PCH.h>
#include <Object.h>

// Default constructor.
Object::Object() :
_animationSpeed(0),
_animated(false),
_nframe(0),
_currentFrame(0),
_frameWidth(0),
_frameHeight(0),
_timeDelta(0)
{
	transform = (dynamic_cast<Transform&>(*(AttachComponent<Transform>())));
}

// Gives the object the given sprite.
bool Object::SetSprite(sf::Texture& texture, bool isSmooth, int frames, int frameSpeed)
{
	// Create a sprite from the loaded texture.
	_sprite.setTexture(texture);

	// Set animation speed.
	_animationSpeed = frameSpeed;

	// Store the number of frames.
	_nframe = frames;

	// Calculate frame dimensions.
	sf::Vector2u texSize = _sprite.getTexture()->getSize();
	_frameWidth = texSize.x / _nframe;
	_frameHeight = texSize.y;

	// Check if animated or static.
	if (frames > 1)
	{
		// Set sprite as animated.
		_animated = true;

		// Set the texture rect of the first frame.
		_sprite.setTextureRect(sf::IntRect(0, 0, _frameWidth, _frameHeight));
	}
	else
	{
		// Set sprite as non animated.
		_animated = false;
	}

	// Set the origin of the sprite.
	_sprite.setOrigin(_frameWidth / 2.f, _frameHeight / 2.f);

	return true;
}

// Returns the object's sprite.
sf::Sprite& Object::GetSprite()
{
	return _sprite;
}

// Sets the position of the object.
void Object::SetPosition(sf::Vector2f position)
{

	transform.position.x = position.x;
	transform.position.y = position.y;
	_sprite.setPosition(position.x, position.y);



}

// Returns the position of the object.
sf::Vector2f Object::GetPosition() const
{
	//return transform.position();
	return transform.position;
}

// Gets the current animation state of the object.
bool Object::IsAnimated()
{
	return _animated;
}

// Sets the animation state of the object.
void Object::SetAnimated(bool isAnimated)
{
	_animated = isAnimated;

	if (isAnimated)
	{
		_currentFrame = 0;
	}
	else
	{
		// set the texture rect of the first frame
		_sprite.setTextureRect(sf::IntRect(0, 0, _frameWidth, _frameHeight));
	}
}

// Draws the object to the given render window.
void Object::Draw(sf::RenderWindow &window, float timeDelta)
{
	// check if the sprite is animated
	if (_animated)
	{
		// add the elapsed time since the last draw call to the aggregate
		_timeDelta += timeDelta;

		// check if the frame should be updated
		if (_timeDelta >= (1.f / _animationSpeed))
		{
			NextFrame();
			_timeDelta = 0;
		}
	}

	window.draw(_sprite);
}

// Advances the sprite forward a frame.
void Object::NextFrame()
{
	// check if we reached the last frame
	if (_currentFrame == (_nframe - 1))
		_currentFrame = 0;
	else
		_currentFrame++;

	// update the texture rect
	_sprite.setTextureRect(sf::IntRect(_frameWidth * _currentFrame, 0, _frameWidth, _frameHeight));
}

// Gets the frame count of the object.
int Object::GetFrameCount() const
{
	return _nframe;
}
