#ifndef SCENENODE_H
#define SCENENODE_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <Command.h>

#include <vector>
#include <memory>


class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;


public:
	SceneNode();

	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);

	void					update(sf::Time dt);

	sf::Vector2f			getWorldPosition() const;
	sf::Transform			getWorldTransform() const;

	void					onCommand(const Command& command, sf::Time dt);
	virtual unsigned int	getCategory() const;

protected:
	virtual void			updateCurrent(sf::Time dt);

private:
	
	void					updateChildren(sf::Time dt);

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	std::vector<Ptr>		_Children;
	SceneNode*				_Parent;
};

#endif