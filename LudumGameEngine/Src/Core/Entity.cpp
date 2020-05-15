#pragma once
#include <iostream>
#include "Entity.h"
#include "Component.h"


Entity::Entity(EntityManager* manager) 
{
	this->isActive = true;
	this->manager = manager;
}

Entity::Entity(EntityManager* manager, std::string name)
{
	this->isActive = true;
	this->name = name;
	this->manager = manager;
}


bool Entity::IsActive() const 
{
	return this->isActive;
}

void Entity::Update(float deltaTime)
{
	for (Component* component : components)
	{
		component->Update(deltaTime);
	}
}

void Entity::Render()
{
	for (Component* component : components)
	{
		component->Render();
	}
}


void Entity::PrintAllComponents()
{
	std::cout << "entity: " << name << std::endl;
	for (Component* component : components)
	{
		std::cout << "\tcomponent: " << component->name << std::endl;
	}
}

void Entity::Destroy()
{
	this->isActive = false;
}