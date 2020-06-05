#pragma once

#include <fstream>
#include <iostream>
#include "Game.h"
#include "Constants.h"
#include "Map.h"
#include "Entity.h"
#include "EntityManager.h"
#include "../Components/TileMapComponent.h"
#include "../Editor/TileGrid.h"

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
	std::vector<editor::MapCoords*> coords = editor::TileGrid::Load(filePath, mapSizeX, mapSizeY, tileSize, scale);
	if (coords.size() == 0) {
		printf("Tile Map File was not loaded\n");
		return;
	}

	for (editor::MapCoords* coord : coords) {
		AddTile(coord->sx, coord->sy, coord->dx, coord->dy);
	}
}

void Map::AddTile(int sourceX, int sourceY, int posX, int posY)
{
	Entity& newEntity = Game::entityManager->AddEntity("Tile", TILE_LAYER);
	newEntity.AddComponent<TileMapComponent>(
		sourceX, sourceY, 
		posX, posY, 
		tileSize, scale, textureId);
}
