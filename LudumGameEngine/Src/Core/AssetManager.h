#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <map>
#include <string>
#include "EntityManager.h"

class AssetManager
{
public:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, Mix_Chunk*> audios;

	AssetManager(EntityManager* manager);
	AssetManager();
	~AssetManager();
	
	void ClearData();
	void AddTexture(std::string textureId, std::string filePath);
	void AddAudio(std::string audioId, std::string filePath);
	SDL_Texture* GetTexture(std::string textureId);
	Mix_Chunk* GetAudioChunk(std::string audioId);
};

