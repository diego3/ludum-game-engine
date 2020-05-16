#pragma once
#include <string>
#include <vector>

#include "Entity.h"
#include "EntityManager.h"

Entity& EntityManager::AddEntity(std::string name)
{
	Entity* e = new Entity(this, name);
	entities.push_back(e);
	// Google the difference
	//entities.emplace_back(e);
	return *e;
}

void EntityManager::AddEntity(Entity* entity)
{
	entities.push_back(entity);

	entity->PrintAllComponents();
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

