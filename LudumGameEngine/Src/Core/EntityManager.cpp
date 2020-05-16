#pragma once
#include <iostream>
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

void EntityManager::PrintAllEntities()
{
	int count = 1;
	for (Entity* entity : entities) {
		std::cout << "entity[" << count << "]: " << entity->name << std::endl;
		entity->PrintAllComponents();
		count++;
	}
}


