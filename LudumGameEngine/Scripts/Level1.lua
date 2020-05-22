Level1 = {
	assets = {
		[0] = {type="texture", id="tank", file="Assets/images/tank-small-right.png"},
		[1] = {type="texture", id="chopper", file="Assets/images/chopper-spritesheet.png"},
		[2] = {type="texture", id="radar", file="Assets/images/radar.png"},
		[3] = {type="texture", id="tile-map", file="Assets/images/jungle.png"},
		[4] = {type="texture", id="explosion", file="Assets/images/explosion-320x320.png"},
		[5] = {type="texture", id="explosion2", file="Assets/images/Explosion-1152x96.png"},
	},
	layers = {
		TILE_LAYER = 0,
		VEGETATION_LAYER = 1,
		ENEMY_LAYER = 2,
		PLAYER_LAYER = 3,
		PROJECTILE_LAYER = 4,
		UI_LAYER = 5
	},
	map = {
		assetId = "tile-map",
		file = "Assets/tilemaps/jungle.map",
		scale = 2,
		tileSize = 32,
		mapSizeX = 25,
		mapSizeY = 20
	},
	entities = {
		[0] = {
			name = "player",
			layer = 3,
			components = {
				transform = {
					position ={x = 240, y = 106},
					velocity = {x = 0, y = 0},
					width = 32,
					height= 32,
					scale = 2,
					rotate = 0
				},
				camera = {},
				cameraShake = {},
				collider = { tag = "PLAYER" },
				sprite = {
					assetId = "chopper",
					animated = true,
					numFrames = 2,
					animationSpeed = 90,
					hasDirections = true,
					isFixed = false
				},
				input = {
					keyboard = {
						up = "up",
						down = "down",
						left = "left",
						right = "right",
						shoot = "space"
					}
				}
			}
		},
		[1] = {
			name = "explosion1",
			layer = 1, -- vegetation layer
			components = {
				transform = {
					position = {x = 300, y = 200},
					velocity = {x = 0, y = 0},
					width = 96,
					height= 96,
					scale = 2,
					rotate = 0
				},
				sprite = {
					assetId = "explosion2",
					animated = true,
					numFrames = 12,
					animationSpeed = 90,
					hasDirections = false,
					isFixed = false
				},
				collider = {tag = "ENEMY"}
			}
		},
		[2] = {
			name = "explosion2",
			layer = 1, -- vegetation layer
			components = {
				transform = {
					position ={ x = 500, y = 200},
					velocity = {x = 0,y = 0},
					width = 96,
					height= 96,
					scale = 2,
					rotate = 0
				},
				sprite = {
					assetId = "explosion2",
					animated = true,
					numFrames = 12,
					animationSpeed = 150,
					hasDirections = false,
					isFixed = false
				}
			}
		},
		[3] = {
			name = "explosion3",
			layer = 1, -- vegetation layer
			components = {
				transform = {
					position ={ x = 800, y = 400},
					velocity = {x = 0,y = 0},
					width = 96,
					height= 96,
					scale = 10,
					rotate = 0
				},
				sprite = {
					assetId = "explosion2",
					animated = true,
					numFrames = 12,
					animationSpeed = 45,
					hasDirections = false,
					isFixed = false
				}
			}
		},
		[4] = {
			name = "explosion4",
			layer = 1, -- vegetation layer
			components = {
				transform = {
					position ={ x = 1200, y = 600},
					velocity = {x = 0,y = 0},
					width = 96,
					height= 96,
					scale = 6,
					rotate = 0
				},
				sprite = {
					assetId = "explosion2",
					animated = true,
					numFrames = 12,
					animationSpeed = 90,
					hasDirections = false,
					isFixed = false
				}
			}
		},
		[5] = {
			name = "radar",
			layer = 1, -- UI LAYER
			components = {
				transform = {
					position ={ x = 720, y = 15},
					velocity = {x = 0,y = 0},
					width = 64,
					height= 64,
					scale = 1,
					rotate = 0
				},
				sprite = {
					assetId = "radar",
					animated = true,
					numFrames = 8,
					animationSpeed = 90,
					hasDirections = false,
					isFixed = true
				}
			}
		},
	}
}

--[[

	-- Challenge: Draw a grid to wrap the image
	Entity& mapa = Game::entityManager->AddEntity("Tile");
	mapa.AddComponent<TransformComponent>(100, 250, 0, 0, 320, 96, 2);
	mapa.AddComponent<SpriteComponent>("tile-map");

	Entity& tank = entityManager->AddEntity("Tank", ENEMY_LAYER);
	tank.AddComponent<TransformComponent>(120, 472, 20, 0, 32, 32, 2);
	tank.AddComponent<SpriteComponent>("tank");

	-- Animaticao nao percorre as colunas ainda....
	Entity& explosion = entityManager->AddEntity("Explosion", ENEMY_LAYER);
	explosion.AddComponent<TransformComponent>(200, 200, 0, 0, 64,64, 2);
	explosion.AddComponent<SpriteComponent>("explosion", 5, 90, false, true);

]]