#pragma once

#include <vector>
#include <map>
#include <string>
#include "EntityManager.h"
#include "Constants.h"

class EntityManager;
class Component;

class Entity 
{
public:
	std::string name;
	std::vector<Component*> components;
	//http://www.cplusplus.com/reference/typeinfo/type_info/
	std::map<const type_info*, Component*> componentsTypeMap;
	LayerType layer;

	bool isActive;
	EntityManager* manager;

	Entity(EntityManager* manager);
	Entity(EntityManager* manager, std::string name, LayerType layer);
	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;

	template<typename T, typename... TArgs>
	T& AddComponent(TArgs... args) {
		T* newComponent = new T(std::forward<TArgs>(args)...);
		newComponent->owner = this;
		
		componentsTypeMap[&typeid(*newComponent)] = newComponent;
		components.push_back(newComponent);

		newComponent->Initialize();
		return *newComponent;
	}

	template<typename T>
	T* GetComponent()
	{
		return static_cast<T*>(componentsTypeMap[&typeid(T)]);
	}

	template<typename T>
	bool HasComponent() const {
		return componentsTypeMap.count(&typeid(T)) > 0;
	}

	void PrintAllComponents();
};