#include <PCH.h>
#include <Audio.h>

Audio::Audio()
{
}


void Audio::PlaySound(sf::Sound & sound, sf::Vector2f position)
{
	// Generate and set a random pitch.
	float pitch = (rand() % 11 + 95) / 100.f;
	sound.setPitch(pitch);

	// Set the position of the sound.
	sound.setPosition(position.x, position.y, 0.f);

	// Play the sound.
	sound.play();
}
void Audio::Play(sf::Vector2f position)
{

	PlaySound(SoundBufferManager::GetSoundbyKey(_id), position);
}



bool Audio::SetSoundBuffer(std::string filePath, bool pos, float a, float d)
{
	int id;

	if (pos)
		id = SoundBufferManager::AddSoundBuffer(filePath, a, d);
	else
		id = SoundBufferManager::AddSoundBuffer(filePath);

	if (id == -1)
		return false;

	_id = filePath;
	return true;
}
