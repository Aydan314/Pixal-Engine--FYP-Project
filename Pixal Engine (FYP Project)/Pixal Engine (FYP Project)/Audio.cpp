#include "Audio.h"

Audio::Audio(std::string filePath, int volume)
{
	m_filePath = filePath;
	m_volume = volume;

	LoadFromFile();
}

Audio::~Audio()
{

}

void Audio::LoadFromFile()
{
	m_mixChunk = Mix_LoadWAV(m_filePath.c_str());
}

void Audio::Play(bool loop)
{
	if (loop) m_channel = Mix_PlayChannel(m_channel, m_mixChunk, -1);
	else m_channel = Mix_PlayChannel(m_channel, m_mixChunk, 0);
}

void Audio::Pause()
{
	Mix_Pause(m_channel);
}

void Audio::SetVolume(float volume)
{
	m_volume = volume;
	Mix_Volume(m_channel, volume);
}

std::string Audio::GetName()
{
	return m_filePath;
}