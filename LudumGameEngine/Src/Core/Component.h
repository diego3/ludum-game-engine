#pragma once
#include <string>
#include "Entity.h"

class Entity;

class Component
{
public:
	std::string name;
	Entity* owner;
	virtual ~Component() {}
	
	virtual void Initialize() {}
	virtual void Update(float deltaTime) {}
	virtual void Render() {}
};
