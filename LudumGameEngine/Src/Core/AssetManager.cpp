#include "AssetManager.h"
#include "TextureManager.h"

AssetManager::AssetManager()
{
}

AssetManager::AssetManager(EntityManager* manager)
{
	manager = manager;
}

AssetManager::~AssetManager()
{
}

void AssetManager::ClearData()
{
	textures.clear();
}

void AssetManager::AddTexture(std::string textureId, std::string filePath)
{
	textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId)
{
	// how to check if exists???
	return textures[textureId];
}
