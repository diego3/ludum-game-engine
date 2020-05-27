#pragma once

#include <SDL.h>
#include <map>
#include <string>
#include "EntityManager.h"

class AssetManager
{
public:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;

	AssetManager(EntityManager* manager);
	AssetManager();
	~AssetManager();
	
	void ClearData();
	void AddTexture(std::string textureId, std::string filePath);
	SDL_Texture* GetTexture(std::string textureId);

};

