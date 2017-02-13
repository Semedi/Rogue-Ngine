#include <PCH.h>
#include <Item.h>

// Default constructor.
Item::Item() :
	_name(""),
	_textOffset({0.f, 0.f})
{
	// Load font.
	_font.loadFromFile("../resources/fonts/ADDSBP__.TTF");
	_text.setFont(_font);

	// Setup the text.
	_text.setCharacterSize(12);
}

// Gets the name of the item.
std::string Item::GetItemName() const
{
	return _name;
}

// Sets the item name.
void Item::SetItemName(std::string name)
{
	// Store new name.
	_name = name;

	// Set the item name.
	std::ostringstream ss;
	ss << _name;
	std::string str(ss.str());
	_text.setString(str);

	// Store the text offset needed when drawing.
	_textOffset = sf::Vector2f(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
}

// Gets the item type.
ITEM Item::GetType() const
{
	return m_type;
}

// Draws the item and its name if it has one.
void Item::Draw(sf::RenderWindow& window, float timeDelta)
{
	// Draw the object.
	Object::Draw(window, timeDelta);

	// Draw the item name.
	_text.setPosition(transform.position.x - _textOffset.x, (transform.position.y - 30.f) - _textOffset.y);
	window.draw(_text);
}