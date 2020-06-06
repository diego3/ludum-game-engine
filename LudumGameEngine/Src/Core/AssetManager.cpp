#include "AssetManager.h"
#include "TextureManager.h"
#include "AudioManager.h"

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

void AssetManager::AddAudio(std::string audioId, std::string filePath)
{
	audios.emplace(audioId, AudioManager::LoadAudio(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId)
{
	// how to check if exists???
	return textures[textureId];
}

Mix_Chunk* AssetManager::GetAudioChunk(std::string audioId) {
	return audios[audioId];
}