#ifndef SOUNDMANAGERBUFFER_H
#define SOUNDMANAGERBUFFER_H

class SoundBufferManager
{
public:
	/**
	 * Default constructor.
	 */
	SoundBufferManager();

	/**
	 * Adds a sound buffer to the manager, and returns its id in the map.
	 * @param filePath The path to the sound to load.
	 * @return The id to the sound buffer created, or the id in the map if it already exists.
	 */
	static int AddSoundBuffer(std::string filePath);
	static int AddSoundBuffer(std::string filePath, float attenuation, float distance);

	/**
	 * Removes a sound buffer from the manager from a given id.
	 * @param soundBufferID The id of the sound buffer to be removed.
	 */
	static void RemoveSoundBuffer(int soundBufferID);

	/**
	 * Gets a sound buffer from its ID.
	 * @param soundBufferId The id of the sound buffer to return.
	 * @return A reference to the sound buffer.
	 */
	static sf::SoundBuffer& GetSoundBuffer(int soundBufferId);
	static sf::SoundBuffer & GetSoundBuffer(std::string key);
	static sf::Sound& GetSound(int id);

	static sf::Sound& GetSoundbyKey(std::string key);

private:
	/**
	 * A map of each sound name with its ID.
	 */
	static std::map<std::string, std::tuple<int, std::unique_ptr<sf::SoundBuffer>, std::unique_ptr<sf::Sound>>> SoundBufferManager::m_soundBuffers;

	/**
	 * The current key value.
	 */
	static int m_currentId;
};
#endif