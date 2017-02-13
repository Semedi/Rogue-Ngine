#include <PCH.h>

std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> TextureManager::_textures;
int TextureManager::_currentId = 0;

// Default Constructor.
TextureManager::TextureManager()
{
}

// Adds a texture to the manager, and returns its id in the map.
int TextureManager::AddTexture(std::string filePath)
{
	// First check if the texture has already been created. If so, simply return that one.
	auto it = _textures.find(filePath);

	if (it != _textures.end())
	{
		return it->second.first;
	}

	// At this point the texture doesn't exists, so we'll create and add it.
	_currentId++;

	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	if (!texture->loadFromFile(filePath))
	{
		return -1;
	}

	_textures.insert(std::make_pair(filePath, std::make_pair(_currentId, std::move(texture))));

	// Return the texture.
	return _currentId;
}

// Removes a texture from the manager from a given id.
void TextureManager::RemoveTexture(int textureID)
{
	for (auto it = _textures.begin(); it != _textures.end(); ++it)
	{
		if (it->second.first == textureID)
		{
			_textures.erase(it->first);
		}
	}
}

// Gets a texture from the texture manager from an ID.
sf::Texture& TextureManager::GetTexture(int textureID)
{
	for (auto it = _textures.begin(); it != _textures.end(); ++it)
	{
		if (it->second.first == textureID)
		{
			return *it->second.second;
		}
	}
}