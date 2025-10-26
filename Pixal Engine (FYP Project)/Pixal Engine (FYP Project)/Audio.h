#pragma once
#include <SDL_mixer.h>
#include <iostream>
#include <string>

class Audio
{
private:
	Mix_Chunk* m_mixChunk = nullptr;
	int m_channel = -1;

	int m_volume = 128;
	std::string m_filePath = "";

public:
	Audio(std::string filePath, int volume);
	~Audio();

	void LoadFromFile();
	void Play(bool loop);
	void Pause();
	void SetVolume(float volume);

	std::string GetName();
};