#ifndef AUDIO_H
#define AUDIO_H

#include "Component.h"

class Audio : public Component
{
public : 

	Audio();
	void Play();
	bool SetSoundBuffer(std::string filePath);
	

	void PlaySound(sf::Sound & sound, sf::Vector2f position = { 0.f, 0.f });

private:
	
	std::string _id;
};

#endif