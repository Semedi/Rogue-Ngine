#ifndef ACCESIBLE_H
#define ACCESIBLE_H

#include <SFML\System\Vector2.hpp>;

class accesible
{
public:
	static  sf::Vector2f playerPositiond;
	static float DistanceBetweenPoints(sf::Vector2f position1, sf::Vector2f position2)
	{
		return (abs(sqrt(((position1.x - position2.x) * (position1.x - position2.x)) + ((position1.y - position2.y) * (position1.y - position2.y)))));
	}
};

#endif

