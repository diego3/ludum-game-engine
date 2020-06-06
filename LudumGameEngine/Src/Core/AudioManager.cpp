#pragma once

#include <SDL_mixer.h>
#include "AudioManager.h"

AudioManager::AudioManager(){
	frequency = 44100;
	format = AUDIO_S16SYS;
	channels = 2;//stereo
	chunksize = 1024;//bytes
	allocateChannels = 4;
}

AudioManager::~AudioManager(){
	Mix_CloseAudio();
}


bool AudioManager::Initialize(){
	// load support for the OGG and MOD sample/music formats
	int sound_flags = MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_MP3;
	int sound_initted = Mix_Init(sound_flags);
	if ((sound_initted & sound_flags) != sound_flags) {
		printf("Mix_Init: Failed to init required ogg, mod and mp3 support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
		return false;
	}

	int i;
	const int total = Mix_GetNumChunkDecoders();
	for (i = 0; i < total; i++) {
		printf("Supported chunk decoder: [%s]\n", Mix_GetChunkDecoder(i));
	}

	if (Mix_OpenAudio(frequency, format, channels, chunksize) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		return false;
	}

	if (Mix_AllocateChannels(allocateChannels) < 0) {
		printf("Unable to allocate mixing channels: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

Mix_Chunk* AudioManager::LoadAudio(std::string audioFilePath) {
	Mix_Chunk* chunk = Mix_LoadWAV(audioFilePath.c_str());
	if (!chunk) {
		printf("AudioManager::LoadAudio error on load file: %s,\n error: %s\n", audioFilePath.c_str(), Mix_GetError());
		return NULL;
	}
	return chunk;
}

void AudioManager::PlayAudio(int channel, Mix_Chunk* chunk, int loop) {
	Mix_PlayChannel(channel, chunk, loop);
}

void AudioManager::PlayOnce(int channel, Mix_Chunk* chunk) {
	PlayAudio(channel, chunk, 0);
}

void AudioManager::PlayOnce(Mix_Chunk* chunk) {
	PlayAudio(-1, chunk, 0);
}
