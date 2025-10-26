#include "AudioManager.h"

AudioManager* AudioManager::m_instance;

AudioManager::AudioManager()
{
	LoadGameAudio();
}

void AudioManager::LoadGameAudio()
{
	for (auto& soundName : SOUNDS_TO_LOAD)
	{
		m_sounds.push_back(Audio(soundName, 128));
	}
}

AudioManager::~AudioManager()
{
	m_instance = nullptr;
}

void AudioManager::PlayAudio(std::string name, int volume, bool loop)
{
	for (auto& sound : m_sounds)
	{
		if (sound.GetName() == name)
		{
			sound.Play(loop);
			sound.SetVolume(volume);
			break;
		}
	}
}

void AudioManager::PauseAudio(std::string name)
{
	for (auto& sound : m_sounds)
	{
		if (sound.GetName() == name)
		{
			sound.Pause();
			break;
		}
	}
}

void AudioManager::SetAudioVolume(std::string name, int volume)
{
	for (auto& sound : m_sounds)
	{
		if (sound.GetName() == name)
		{
			sound.SetVolume(volume);
			break;
		}
	}
}

