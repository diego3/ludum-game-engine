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

	template<typename T, typename... TArgs>
	T& AddComponent(TArgs... args) {
		T* newComponent = new T(std::forward<TArgs>(args)...);
		newComponent->owner = this;
		components.push_back(newComponent);
		newComponent->Initialize();
		return *newComponent;
	}

	void PrintAllComponents();
};