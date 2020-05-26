#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Entity.h"
#include "EntityManager.h"
#include "Constants.h"
#include "Collision.h"
#include "../Components/BoxColliderComponent.h"

Entity& EntityManager::AddEntity(std::string name, LayerType layer)
{
	Entity* e = new Entity(this, name, layer);
	entities.emplace_back(e);
	return *e;
}

void EntityManager::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

Entity* EntityManager::FindEntityByName(std::string name) {
	for (Entity* entity : entities) {
		if (entity->name.compare(name) == 0) {
			return entity;
		}
	}
	return NULL;
}

Entity* EntityManager::Instantiate(std::string name, LayerType layer) {
	Entity* e = new Entity(this, name, layer);


	return e;
}

// https://gameprogrammingpatterns.com/spatial-partition.html
CollisionType EntityManager::CheckCollisions() {
	for (Entity* entity : entities) {
		if (entity->layer == LayerType::TILE_LAYER || entity->layer == LayerType::UI_LAYER) continue;
		if (!entity->HasComponent<BoxColliderComponent>()) continue;

		//std::cout << "checking: "<< entity->name << std::endl;

		BoxColliderComponent* collider = entity->GetComponent<BoxColliderComponent>();
		for (Entity* other : entities) {
			if (other->layer == LayerType::TILE_LAYER || other->layer == LayerType::UI_LAYER) continue;
			if (!other->HasComponent<BoxColliderComponent>() || other->name.compare(entity->name) == 0) continue;
			
			BoxColliderComponent* otherCollider = other->GetComponent<BoxColliderComponent>();

			/*std::cout << other->name << " other collider {" <<
				otherCollider->collider.x << "," << 
				otherCollider->collider.y << "," <<
				otherCollider->collider.w << "," <<
				otherCollider->collider.h << "}" << std::endl;*/

			if (Collision::CheckRectangleCollision(collider->collider, otherCollider->collider)) {
				///std::cout << "\t COLLISION ENTER tag(" << otherCollider->colliderTag << ")"<< std::endl;

				if (otherCollider->colliderTag.compare("ENEMY") == 0) {
					return CollisionType::PLAYER_ENEMY;
				}
				if (otherCollider->colliderTag.compare("PROJECTILE") == 0) {
					return CollisionType::PLAYER_PROJECTILE;
				}
				if (otherCollider->colliderTag.compare("NEXT_LEVEL") == 0) {
					return CollisionType::NEXT_LEVEL;
				}
			}
			//else {
				///std::cout << "\t COLLISION OUT "<< std::endl;
			//}
		}
	}
	return CollisionType::NONE;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer)
{
	std::vector<Entity*> selected;
	for (Entity* entity : entities) {
		if (entity->layer == layer) {
			selected.emplace_back(entity);
		}
	}
	return selected;
}

void EntityManager::Render()
{
	// TODO IMPROVE THIS SOON
	// map<layer, vector<Entity*>>
	for (int layerNum = 0; layerNum < NUM_LAYERS; layerNum++) {
		for (Entity* entity : GetEntitiesByLayer(static_cast<LayerType>(layerNum))) {
			entity->Render();
		}
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


