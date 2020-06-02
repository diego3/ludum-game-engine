#pragma once

#include <vector>
#include "../Core/Component.h"
#include "TransformComponent.h"
#include "../Core/AssetManager.h"
#include "../../Libs/glm/glm/glm.hpp"
#include "../Core/Game.h"
#include "../Core/TextureManager.h"

#include "../Core/Projectile.h"

class ProjectileComponent : public Component {
public:
	TransformComponent* transform;
	
	int pool;

	std::vector<Projectile*> projectiles;

	bool Play = false;

	ProjectileComponent(std::string assetId, float speed, int width, int height, int scale, int duration, int pool) {

		this->pool = pool;
		for (int i = 0; i < this->pool; i++) {
			Projectile* newP = new Projectile(assetId, speed, width, height, scale, duration);
			projectiles.push_back(newP);
		}

		transform = NULL;
	}

	~ProjectileComponent() {
		
	}

	void Initialize() override {
		transform = owner->GetComponent<TransformComponent>();
		for (Projectile* p : projectiles) {
			p->Initialize(transform);
		}
		printf("projectiles %d\n", projectiles.size());
	}

	void Update(float deltaTime) override {
		for (Projectile* p : projectiles) {
			if (Play && !p->playing) {
				p->playing = true;
			}
			p->Update(deltaTime);
		}
	}

	void Render() override {
		for (Projectile* p : projectiles) {
			p->Render();
		}
	}

	void Destroy() {

	}
};