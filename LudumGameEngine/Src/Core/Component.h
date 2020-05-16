#pragma once
#include <string>
#include "Entity.h"

class Entity;

class Component
{
public:
	Entity* owner;
	virtual ~Component() {}
	
	virtual void Initialize() {}
	virtual void Update(float deltaTime) {}
	virtual void Render() {}
};
