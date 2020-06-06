#pragma once

#include <iostream>
#include <string>
#include <SDL_mixer.h>

class AudioManager {

public:
	int frequency;
	int format;
	int channels;
	int chunksize;
	int allocateChannels;


	AudioManager();

	~AudioManager();

	bool Initialize();

	static Mix_Chunk* LoadAudio(std::string audioFilePath);
	void PlayAudio(int channel, Mix_Chunk* chunk, int loop);
	void PlayOnce(int channel, Mix_Chunk* chunk);
	void PlayOnce(Mix_Chunk* chunk);
};