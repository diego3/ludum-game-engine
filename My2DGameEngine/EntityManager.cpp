#pragma once
#include "Entity.h"
#include "EntityManager.h"
#include <string>
#include <vector>

Entity& EntityManager::AddEntity(std::string name)
{
	Entity* e = new Entity(this, name);
	entities.push_back(e);
	// Google the difference
	//entities.emplace_back(e);
	return *e;
}

void EntityManager::Render()
{
	for (Entity* entity : entities)
	{
		entity->Render();
	}
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


