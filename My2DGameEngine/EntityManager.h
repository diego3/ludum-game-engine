#pragma once
#include <vector>
#include <string>

class Entity;

class EntityManager
{
public:
	std::vector<Entity*> entities;

	void Update(float deltaTime);
	void Render();
	bool HasNoEntities();
	Entity& AddEntity(std::string name);
	void AddEntity(Entity* entity);
	std::vector<Entity*> GetEntities() const;
	unsigned int GetEntityCount();
};