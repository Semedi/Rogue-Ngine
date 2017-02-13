#include <PCH.h>
#include <Transform.h>

Transform::Transform() :
position({0.f, 0.f})
{
}



void Transform::SetPosition(sf::Vector2f pos)
{
	position = pos;
}

sf::Vector2f& Transform::GetPosition()
{
	return position;
}