#include <PCH.h>

std::map<std::string, std::tuple<int, std::unique_ptr<sf::SoundBuffer>, std::unique_ptr<sf::Sound>>> SoundBufferManager::m_soundBuffers;
int SoundBufferManager::m_currentId = 0;

// Default Constructor.
SoundBufferManager::SoundBufferManager()
{
}

// Adds a sound to the manager, and returns its id in the map.
int SoundBufferManager::AddSoundBuffer(std::string filePath)
{
	// First check if the sound has already been created. If so, simply return that one.
	auto it = m_soundBuffers.find(filePath);

	if (it != m_soundBuffers.end())
	{
		return std::get<0>(it->second);

	}

	// At this point the texture doesn't exists, so we'll create and add it.
	m_currentId++;

	std::unique_ptr<sf::SoundBuffer> buffer = std::make_unique<sf::SoundBuffer>();
	if (!buffer->loadFromFile(filePath))
	{
		return -1;
	}

	std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>();
	sound->setBuffer(*buffer);
	sound->setRelativeToListener(true);

	m_soundBuffers.insert(std::make_pair(filePath, std::make_tuple(m_currentId, std::move(buffer), std::move(sound))));

	// Return the texture.
	return m_currentId;
}

int SoundBufferManager::AddSoundBuffer(std::string filePath, float attenuation, float distance)
{
	// First check if the sound has already been created. If so, simply return that one.
	auto it = m_soundBuffers.find(filePath);

	if (it != m_soundBuffers.end())
	{
		return std::get<0>(it->second);

	}

	// At this point the texture doesn't exists, so we'll create and add it.
	m_currentId++;

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

	m_soundBuffers.insert(std::make_pair(filePath, std::make_tuple(m_currentId, std::move(buffer), std::move(sound))));

	// Return the texture.
	return m_currentId;
}

// Gets a texture from the texture manager from an ID.
sf::SoundBuffer& SoundBufferManager::GetSoundBuffer(int textureId)
{
	for (auto it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it)
	{

		if (std::get<0>(it->second) == textureId)
			return *std::get<1>(it->second);
	}
}

sf::SoundBuffer& SoundBufferManager::GetSoundBuffer(std::string key)
{
	return *std::get<1>(m_soundBuffers[key]);
}

sf::Sound & SoundBufferManager::GetSound(int textureId)
{
	// TODO: insert return statement here
	for (auto it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it)
	{

		if (std::get<0>(it->second) == textureId)
			return *std::get<2>(it->second);
	}
}

sf::Sound & SoundBufferManager::GetSoundbyKey(std::string key)
{
	// TODO: insert return statement here
	return *std::get<2>(m_soundBuffers[key]);
}
