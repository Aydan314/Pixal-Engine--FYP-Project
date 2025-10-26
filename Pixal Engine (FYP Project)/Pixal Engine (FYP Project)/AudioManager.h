#pragma once
#include "Audio.h"
#include "Commons.h"
#include <vector>
#include <iostream>

class AudioManager
{
private:
	AudioManager();
	std::vector<Audio> m_sounds = {};
	static AudioManager* m_instance;

	void LoadGameAudio();

public:
	static inline AudioManager* Instance() {
		if (!m_instance)
		{
			m_instance = new AudioManager();
		}
		return m_instance;
	}

	~AudioManager();

	void PlayAudio(std::string name, int volume = 128, bool loop = false);
	void PauseAudio(std::string name);
	void SetAudioVolume(std::string name, int volume);
};


