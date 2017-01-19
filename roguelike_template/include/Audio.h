#ifndef AUDIO_H
#define AUDIO_H

#include "Component.h"

class Audio : public Component
{
public : 

	Audio();
	void Play(sf::Vector2f position = { 0.f, 0.f });
	bool SetSoundBuffer(std::string filePath, bool pos = false, float a = 5.0f, float d = 80.0f);
	

	void PlaySound(sf::Sound & sound, sf::Vector2f position = { 0.f, 0.f });

private:
	
	std::string _id;
};

#endif