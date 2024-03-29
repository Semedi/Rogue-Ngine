#include <PCH.h>
#include <Enemy.h>

// Default constructor.
Enemy::Enemy()
{
	// Set stats.
	_health = std::rand() % 41 + 80;
	_attack = std::rand() % 5 + 6;
	_defense = std::rand() % 5 + 6;
	_strength = std::rand() % 5 + 6;
	_dexterity = std::rand() % 5 + 6;
	_stamina = std::rand() % 5 + 6;

	// Set speed.
	_speed = rand() % 51 + 150;

	/* DEBUG 
	int textureID = TextureManager::AddTexture("../resources/spr_path.png");
	_pathSprite.setTexture(TextureManager::GetTexture(textureID));

	// Set the sprite origin.
	sf::Vector2u spriteSize = _pathSprite.getTexture()->getSize();
	_pathSprite.setOrigin(sf::Vector2f(static_cast<float>(spriteSize.x / 2), static_cast<float>(spriteSize.y / 2)));
	_font.loadFromFile("../resources/fonts/04B_03__.TTF");

	_text.setFont(_font);
	_text.setCharacterSize(12);
	/**************************************************************************************************************************/


	AttachComponent<Audio>()->SetSoundBuffer("../resources/sounds/snd_enemy_dead.wav", true);


}


// Applies the given amount of damage to the enemy.
void Enemy::Damage(int damage)
{
	_health -= damage;
}

// Checks if the enemy has taken enough damage that they are now dead.
bool Enemy::IsDead()
{
	return (_health <= 0);
}
void Enemy::UpdatePathfinding(Level & level, sf::Vector2f playerPosition)
{
	//variables
	std::vector<Tile*> openList;
	std::vector<Tile*> closedList;
	std::vector<Tile*> pathList;
	std::vector<Tile*>::iterator position;
	Tile* currentNode;

	//Reset all nodes
	level.ResetNodes();

	//Store the start and goal nodes.
	Tile* startNode = level.GetTile(transform.position);
	Tile* goalNode = level.GetTile(playerPosition);

	// Check we have a valid path to find. If not we can just end the function as there's no path to find.
	if (startNode == goalNode)
	{
		// Clear the vector of target positions.
		_targetPositions.clear();

		// Exit the function.
		return;
	}



	// Pre-compute our H cost (estimated cost to goal) for each node.
	for (int i = 0; i < level.GetSize().x; i++)
	{
		for (int j = 0; j < level.GetSize().y; j++)
		{
			int rowOffset, heightOffset;
			Tile* node = level.GetTile(i, j);

			heightOffset = abs(node->rowIndex - goalNode->rowIndex);
			rowOffset = abs(node->columnIndex - goalNode->columnIndex);

			node->H = heightOffset + rowOffset;
		}
	}

	// Add the start node to the open list.
	openList.push_back(startNode);

	// While we have values to check in the open list.
	while (!openList.empty())
	{
		// Find the node in the open list with the lowest F value and mark it as current.
		//int lowestF = INT_MAX;
		int lowestF = 12393221;

		for (Tile* tile : openList)
		{
			if (tile->F < lowestF)
			{
				lowestF = tile->F;
				currentNode = tile;
			}
		}

		// Remove the current node from the open list and add it to the closed list.
		position = std::find(openList.begin(), openList.end(), currentNode);
		if (position != openList.end())
			openList.erase(position);

		closedList.push_back(currentNode);

		// Find all valid adjacent nodes.
		std::vector<Tile*> adjacentTiles;
		Tile* node;

		// Top.
		node = level.GetTile(currentNode->columnIndex, currentNode->rowIndex - 1);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(level.GetTile(currentNode->columnIndex, currentNode->rowIndex - 1));
		}

		// Right.
		node = level.GetTile(currentNode->columnIndex + 1, currentNode->rowIndex);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(level.GetTile(currentNode->columnIndex + 1, currentNode->rowIndex));
		}

		// Bottom.
		node = level.GetTile(currentNode->columnIndex, currentNode->rowIndex + 1);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(level.GetTile(currentNode->columnIndex, currentNode->rowIndex + 1));
		}

		// Left.
		node = level.GetTile(currentNode->columnIndex - 1, currentNode->rowIndex);
		if ((node != nullptr) && (level.IsFloor(*node)))
		{
			adjacentTiles.push_back(level.GetTile(currentNode->columnIndex - 1, currentNode->rowIndex));
		}



		// For all adjacent nodes.
		for (Tile* node : adjacentTiles)
		{
			// If the node is our goal node.
			if (node == goalNode)
			{
				// Parent the goal node to current.
				node->parentNode = currentNode;

				// Store the current path.
				while (node->parentNode != nullptr)
				{
					pathList.push_back(node);
					node = node->parentNode;
				}

				// Empty the open list and break out of our for loop.
				openList.clear();
				break;
			}

			else
			{
				// If the node is not in the closed list.
				position = std::find(closedList.begin(), closedList.end(), node);
				if (position == closedList.end())  //pointer not found, if we found the pointer it means that the tile has been already calculated
				{
					// If the node is not in the open list.
					position = std::find(openList.begin(), openList.end(), node);
					if (position == openList.end()) //pointer not found, if we found the pointer it's going to be processed in the next iteration anyways so we should ignore it
					{
						// Add the node to the open list.
						openList.push_back(node);

						// Set the parent of the node to the current node.
						node->parentNode = currentNode; // this will be used to remember the predecessor

						/*
						* We already know that the movement cost between nodes is 10
						*/

						// Calculate G (total movement cost so far) cost.
						node->G = currentNode->G + 10;

						// Calculate the F (total movement cost + heuristic) cost.
						node->F = node->G + node->H;
					}
					else
					{
						// Check if this path is quicker that the other.
						int tempG = currentNode->G + 10;

						// Check if tempG is faster than the other. I.e, whether it's faster to go A->C->B that A->C.
						if (tempG < node->G)
						{
							// Re-parent node to this one.
							node->parentNode = currentNode;
						}
					}
				}
			}

		}


	}//main loop

	 // Clear the vector of target positions.
	_targetPositions.clear();

	// Store the node locations as the enemies target locations.
	for (Tile* tile : pathList)
	{
		_targetPositions.push_back(level.GetActualTileLocation(tile->columnIndex, tile->rowIndex));
	}

	// Reverse the target position as we read them from goal to origin and we need them the other way around.
	std::reverse(_targetPositions.begin(), _targetPositions.end());
}

void Enemy::Update(float timeDelta)
{
	// Move towards current target location.
	if (!_targetPositions.empty())
	{
		sf::Vector2f targetLocation = _targetPositions.front();
		_velocity = sf::Vector2f(targetLocation.x - transform.position.x, targetLocation.y - transform.position.y);

		if (abs(_velocity.x) < 10.f && abs(_velocity.y) < 10.f)
		{
			_targetPositions.erase(_targetPositions.begin());
		}
		else
		{
			float length = sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
			_velocity.x /= length;
			_velocity.y /= length;

			transform.position.x += _velocity.x * (_speed * timeDelta);
			transform.position.y += _velocity.y * (_speed * timeDelta);

			_sprite.setPosition(transform.position);
		}

		// Call Entity update.
		Entity::Update(timeDelta);
	}
}

void Enemy::Draw(sf::RenderWindow & window, float timeDelta)
{
	Object::Draw(window, timeDelta);


	/* DEBUG*/
	/******************************************************/
	// DEBUG Draw the current path
	for (int i = 0; i < _targetPositions.size(); i++)
	{
		_pathSprite.setPosition(_targetPositions[i]);
		window.draw(_pathSprite);

		// set the path index
		std::ostringstream ss;
		ss << i;
		std::string str(ss.str());
		_text.setString(str);
		_text.setPosition(_targetPositions[i]);
		window.draw(_text);

	}

	/******************************************************/

}
