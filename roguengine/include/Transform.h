#ifndef TRANSFORM_H
#define TRANSFORM_H


#include <Component.h>

class Transform : public Component
{
	public:
		Transform();
		void SetPosition(sf::Vector2f position);
		sf::Vector2f& GetPosition();
		sf::Vector2f position;

	private:
		
		
	
};

#endif
