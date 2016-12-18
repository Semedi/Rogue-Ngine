#include "PCH.h"
#include "Transform.h"

Transform::Transform() :
m_position({0.f, 0.f})
{
}



void Transform::SetPosition(sf::Vector2f pos)
{
	m_position = pos;
}

sf::Vector2f& Transform::GetPosition()
{
	return m_position;
}