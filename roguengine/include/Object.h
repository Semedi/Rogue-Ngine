#ifndef OBJECT_H
#define OBJECT_H

#include <Component.h>
#include <Transform.h>
#include <Audio.h>
#include <Sprite.h>
#include <SceneNode.h>

class Object : public SceneNode
{
public:
	/**
	 * Default constructor.
	 */
	Object();

	/**
	 * Updates the game object. Called once per tick.
	 * This is a pure virtual function, and must be implemented by extending classes.
	 * @param timeDelta The time elapsed since the last tick in MS.
	 */
	virtual void Update(float timeDelta) {};

	/**
	 * Draws the object to the screen at its current position.
	 * @param window The render window to draw the object to.
	 * @param tileDelta The time, in MS, since the last draw call.
	 */
	virtual void Draw(sf::RenderWindow &window, float timeDelta);

	/**
	 * Sets the position of the object on screen. This is relative to the top-left of the game window.
	 * @param position The new position of the player.
	 */
	void SetPosition(sf::Vector2f position);

	/** 
	 * Returns the position of the object. This is relative to the top-left of the game window.
	 * @return The position of the object
	 */
	sf::Vector2f GetPosition() const;

	/**
	 * Creates and sets the object sprite.
	 * This function takes the location to a resource, and from that create a texture and sprite.
	 * You can optionally specify animation properties. If set the frame dimensions will be calculated automatically.
	 * If left blank, the whole resource will be used.
	 * @param fileName The path to the resource that you wish to load, relative to the project.
	 * @param frames The number of frames in the sprite. Defaults to 1.
	 * @param frameSpeed The speed that the animation plays at. Defaults to 1.
	 * @return true if the operation succeeded.
	 */
	bool SetSprite(sf::Texture& texture, bool isSmooth, int frames = 1, int frameSpeed = 0);

	/**
	 * Returns a reference the object's sprite.
	 * @return A reference to the object's sprite.
	 */
	sf::Sprite& GetSprite();

	/**
	 * Get the number of frames the object has.
	 * @return The number of frames the object has.
	 */
	int GetFrameCount() const;

	/**
	 * Gets the current animation state of the object.
	 * @return The current animation state of the object.
	 */
	bool IsAnimated();

	/**
	* Sets the animation state of the object.
	* @param isAnimated The new animation state of the object.
	*/
	void SetAnimated(bool isAnimated);


	/* Attach the component */
	template <typename T>
	std::shared_ptr<T> AttachComponent()
	{
		std::shared_ptr<T> newComponent = std::make_shared<T>();

		//check if we already have th ecomponent
		for (std::shared_ptr<Component>& existingComponent : _components)
		{
			//exists
			if (std::dynamic_pointer_cast<T>(existingComponent))
			{
				existingComponent = newComponent;
				return newComponent;

			}
		}
		_components.push_back(newComponent);
		return newComponent;

	}

	/* Get Component*/
	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (std::shared_ptr<Component>& existingComponent : _components)
		{
			if (std::dynamic_pointer_cast<T>(existingComponent))
				return std::dynamic_pointer_cast<T>(existingComponent);
		}
		return nullptr;
	}
	

protected:

	
	/**
	 * The object's sprite.
	 */
	sf::Sprite _sprite;

	/**
	 * Transform component, position
	 */
	Transform transform;

	virtual void updateCurrent(sf::Time dt) {

		float timeDelta = dt.asSeconds();
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
	};


private:

	/**
	 * Advances the sprite by a frame.
	 */
	void NextFrame();

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}

	

private:
	bool _animated; //Used to determine if the given sprite is animated.
	float _timeDelta; //An aggregate of the time passed between draw calls.
	int _animationSpeed; //The animation speed of the image if applicable, Value is frames per second.
	int _nframe; //The total number of frames the sprite has.
	int _currentFrame; //The current frame of the sprite.
	int _frameWidth; //The width of each frame of the animated sprite if applicable.
	int _frameHeight; //The height of each frame of the animated sprite if applicable.
	std::vector<std::shared_ptr<Component>> _components; //Collection 4 all the components attached to the object
};
#endif