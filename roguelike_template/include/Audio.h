#ifndef AUDIO_H
#define AUDIO_H

#include "Component.h"
#include "SFML/Audio.hpp"

class Audio : public Component
{
public : 
	Audio();
	bool SetSoundBuffer(sf::SoundBuffer& buffer);
	bool SetSoundBuffer(std::string filePath);

private:
	sf::Sound m_sound;

};

#endif