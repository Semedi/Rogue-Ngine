#include <PCH.h>

std::map<std::string, std::tuple<int, std::unique_ptr<sf::SoundBuffer>, std::unique_ptr<sf::Sound>>> SoundBufferManager::_soundBuffers;
int SoundBufferManager::_currentId = 0;

// Default Constructor.
SoundBufferManager::SoundBufferManager()
{
}

// Adds a sound to the manager, and returns its id in the map.
int SoundBufferManager::AddSoundBuffer(std::string filePath)
{
	// First check if the sound has already been created. If so, simply return that one.
	auto it = _soundBuffers.find(filePath);

	if (it != _soundBuffers.end())
	{
		return std::get<0>(it->second);

	}

	// At this point the texture doesn't exists, so we'll create and add it.
	_currentId++;

	std::unique_ptr<sf::SoundBuffer> buffer = std::make_unique<sf::SoundBuffer>();
	if (!buffer->loadFromFile(filePath))
	{
		return -1;
	}

	std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>();
	sound->setBuffer(*buffer);
	sound->setRelativeToListener(true);

	_soundBuffers.insert(std::make_pair(filePath, std::make_tuple(_currentId, std::move(buffer), std::move(sound))));

	// Return the texture.
	return _currentId;
}

int SoundBufferManager::AddSoundBuffer(std::string filePath, float attenuation, float distance)
{
	// First check if the sound has already been created. If so, simply return that one.
	auto it = _soundBuffers.find(filePath);

	if (it != _soundBuffers.end())
	{
		return std::get<0>(it->second);

	}

	// At this point the texture doesn't exists, so we'll create and add it.
	_currentId++;

	std::unique_ptr<sf::SoundBuffer> buffer = std::make_unique<sf::SoundBuffer>();
	if (!buffer->loadFromFile(filePath))
	{
		return -1;
	}

	std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>();
	sound->setBuffer(*buffer);
	sound->setRelativeToListener(true);
	sound->setAttenuation(5.0f);
	sound->setMinDistance(80.0f);

	_soundBuffers.insert(std::make_pair(filePath, std::make_tuple(_currentId, std::move(buffer), std::move(sound))));

	// Return the texture.
	return _currentId;
}

// Gets a texture from the texture manager from an ID.
sf::SoundBuffer& SoundBufferManager::GetSoundBuffer(int textureId)
{
	for (auto it = _soundBuffers.begin(); it != _soundBuffers.end(); ++it)
	{

		if (std::get<0>(it->second) == textureId)
			return *std::get<1>(it->second);
	}
}

sf::SoundBuffer& SoundBufferManager::GetSoundBuffer(std::string key)
{
	return *std::get<1>(_soundBuffers[key]);
}

sf::Sound & SoundBufferManager::GetSound(int textureId)
{
	// TODO: insert return statement here
	for (auto it = _soundBuffers.begin(); it != _soundBuffers.end(); ++it)
	{

		if (std::get<0>(it->second) == textureId)
			return *std::get<2>(it->second);
	}
}

sf::Sound & SoundBufferManager::GetSoundbyKey(std::string key)
{
	// TODO: insert return statement here
	return *std::get<2>(_soundBuffers[key]);
}
