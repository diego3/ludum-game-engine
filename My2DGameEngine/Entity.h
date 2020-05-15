#pragma once

#include <vector>
#include <string>

class EntityManager;
class Component;

class Entity 
{
public:
	std::string name;
	std::vector<Component*> components;
	bool isActive;
	EntityManager* manager;

	Entity(EntityManager* manager);
	Entity(EntityManager* manager, std::string name);
	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;
};