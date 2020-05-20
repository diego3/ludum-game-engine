#pragma once
#include <iostream>
#include "Entity.h"
#include "Component.h"
#include "Constants.h"


Entity::Entity(EntityManager* manager) 
{
	this->isActive = true;
	this->manager = manager;
}

Entity::Entity(EntityManager* manager, std::string name, LayerType layer)
{
	this->isActive = true;
	this->name = name;
	this->manager = manager;
	this->layer = layer;
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
	for (auto& component : components)
	{
		std::cout << "\tcomponent: " << typeid(*component).name() << std::endl;
	}
}

void Entity::Destroy()
{
	this->isActive = false;
}