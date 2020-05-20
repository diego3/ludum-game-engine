#pragma once

#include <fstream>
#include <iostream>
#include "Game.h"
#include "Constants.h"
#include "Map.h"
#include "Entity.h"
#include "EntityManager.h"
#include "../Components/TileMapComponent.h"

//extern EntityManager* entityManager;

Map::Map(std::string textureId, int scale, int size)
{
	this->textureId = textureId;
	this->scale = scale;
	this->tileSize = size;
}

Map::~Map()
{
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY)
{
	std::fstream file;
	file.open(filePath);
	
	// rows
	for (int y = 0; y < mapSizeY; y++) {
		// columns
		for (int x = 0; x < mapSizeX; x++) {
			char ch;
			file.get(ch);
			//int chint = atoi(&ch);
			//std::cout << "(" << chint;
			int sourceY = atoi(&ch) * tileSize;

			file.get(ch);
			//chint = atoi(&ch);
			//std::cout << chint;
			int sourceX = atoi(&ch) * tileSize;

			int posX = x * (scale * tileSize);
			int posY = y * (scale * tileSize);
			//std::cout << ") src[" << sourceX << ", " << sourceY << "]";
			//std::cout << " pos[" << posX << ", " << posY << "]" << std::endl;
			
			AddTile(sourceX, sourceY, posX, posY);

			file.ignore();
		}
	}

	file.close();
}

void Map::AddTile(int sourceX, int sourceY, int posX, int posY)
{
	Entity& newEntity = Game::entityManager->AddEntity("Tile", TILE_LAYER);
	newEntity.AddComponent<TileMapComponent>(
		sourceX, sourceY, 
		posX, posY, 
		tileSize, scale, textureId);
}
