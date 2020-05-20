#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Entity.h"
#include "EntityManager.h"
#include "Constants.h"

Entity& EntityManager::AddEntity(std::string name, LayerType layer)
{
	Entity* e = new Entity(this, name, layer);
	entities.emplace_back(e);
	return *e;
}

void EntityManager::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer)
{
	std::vector<Entity*> selected;
	for (Entity* entity : entities) {
		if (entity->layer == layer) {
			selected.emplace_back(entity);
		}
	}
	return selected;
}

void EntityManager::Render()
{
	// TODO IMPROVE THIS SOON
	// map<layer, vector<Entity*>>
	for (int layerNum = 0; layerNum < NUM_LAYERS; layerNum++) {
		for (Entity* entity : GetEntitiesByLayer(static_cast<LayerType>(layerNum))) {
			entity->Render();
		}
	}

	/**
	for (Entity* entity : entities)
	{
		entity->Render();
	}*/
}

void EntityManager::Update(float deltaTime)
{
	for (Entity* entity : entities)
	{
		entity->Update(deltaTime);
	}
}

bool EntityManager::HasNoEntities()
{
	return entities.empty();
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return entities;
}

unsigned int EntityManager::GetEntityCount()
{
	return entities.size();
}

void EntityManager::PrintAllEntities()
{
	int count = 1;
	for (Entity* entity : entities) {
		std::cout << "entity[" << count << "]: " << entity->name << std::endl;
		entity->PrintAllComponents();
		count++;
	}
}


