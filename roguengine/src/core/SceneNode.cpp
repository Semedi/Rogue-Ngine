#include <SceneNode.h>

#include <algorithm>
#include <cassert>
#include <PCH.h>

SceneNode::SceneNode()
	: _Children()
	, _Parent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->_Parent = this;
	_Children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(_Children.begin(), _Children.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != _Children.end());

	Ptr result = std::move(*found);
	result->_Parent = nullptr;
	_Children.erase(found);

	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time)
{
	// Do nothing by default
	
}

void SceneNode::updateChildren(sf::Time dt)
{
	FOREACH(Ptr& child, _Children)
		child->update(dt);
}

//override from drawble, this function make possible to draw the object on the screen passed to a window
//in our tree structure we want to draw ourselves and then childrens
void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	FOREACH(const Ptr& child, _Children)
		child->draw(target, states);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->_Parent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
	// Command current node, if category matches
	if (command.category & getCategory())
		command.action(*this, dt);

	// Command children
	FOREACH(Ptr& child, _Children)
		child->onCommand(command, dt);
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}
