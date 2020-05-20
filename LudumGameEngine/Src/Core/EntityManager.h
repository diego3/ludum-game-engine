#pragma once
#include <vector>
#include <string>
#include "EntityManager.h"
#include "Constants.h"

class Entity;

class EntityManager
{
public:
	std::vector<Entity*> entities;

	void Update(float deltaTime);
	void Render();
	bool HasNoEntities();
	Entity& AddEntity(std::string name, LayerType layer);
	void AddEntity(Entity* entity);
	std::vector<Entity*> GetEntitiesByLayer(LayerType layer);
	std::vector<Entity*> GetEntities() const;
	unsigned int GetEntityCount();
	void PrintAllEntities();
};