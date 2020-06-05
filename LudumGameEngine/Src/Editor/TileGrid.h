#pragma once

#include <vector>
#include <SDL.h>

#include "Tile.h"
#include "SpriteSheet.h"
#include "../Util/FileUtil.h"

namespace editor {
	class MapCoords {
	public:
		int sx;
		int sy;
		int dx;
		int dy;
		MapCoords(int sourceX, int sourceY, int destX, int destY) {
			sx = sourceX;
			sy = sourceY;
			dx = destX;
			dy = destY;
		}
	};

	class TileGrid {
	private:
		std::vector<Tile*> tiles;
		int width;
		int height;
		int rectSize;

		int gridSizeX;
		int gridSizeY;

		SDL_Renderer* renderer;
		SpriteSheet* sprite;
	public:
		TileGrid(SDL_Renderer* render, SpriteSheet* sprite, int sizeX, int sizeY, int rectSize) {
			this->renderer = render;
			this->sprite = sprite;
			this->width = sizeX;
			this->height = sizeY;
			this->rectSize = rectSize;
			this->gridSizeX = width / rectSize;//  800/32 = 25units
			this->gridSizeY = height / rectSize;// 600/32 = 18.75units or 19
		}

		bool Initialize() {
			
			for (int i = 0; i < gridSizeY; i++) {
				for (int j = 0; j < gridSizeX; j++) {
					Tile* t = new Tile(0, 0, 400 + (j * rectSize), (i * rectSize));
					
					//TODO remove, just for tests (starts all blue)
					t->IsSelected = true;
					t->index = 0;

					tiles.push_back(t);
				}
			}

			return true;
		}

		void Save(std::string filePath) {
			std::string str = "";
			std::string comma = "";
			int x = 0;
			for (Tile* tile : tiles) {
				if (tile->index < 10) {
					str += "0";
				}
				
				str += std::to_string(tile->index);
				
				if (x != (gridSizeX-1)) {
					str += ",";
					x++;
				}
				else if (x == (gridSizeX-1)) {
					str += "\n";
					x = 0;
				}
			}

			std::cout << "map:" << std::endl;
			std::cout << str << std::endl;

			FileUtil::WriteFile(filePath, str);
		}

		static std::vector<MapCoords*> Load(std::string filePath, int mapSizeX, int mapSizeY, int spriteSize, int scale) {
			std::vector<MapCoords*> result;

			std::fstream file;
			file.open(filePath);
			if (!file.is_open()) {
				printf("Could not open file: %s\n", filePath);
				return result;
			}

			// rows
			for (int y = 0; y < mapSizeY; y++) {
				// columns
				for (int x = 0; x < mapSizeX; x++) {
					char ch;
					file.get(ch);
					//int chint = atoi(&ch);
					//std::cout << "(" << chint;
					int sourceY = atoi(&ch) * spriteSize;

					file.get(ch);
					//chint = atoi(&ch);
					//std::cout << chint;
					int sourceX = atoi(&ch) * spriteSize;

					int dX = x * (scale * spriteSize);
					int dY = y * (scale * spriteSize);
					//std::cout << ") src[" << sourceX << ", " << sourceY << "]";
					//std::cout << " pos[" << posX << ", " << posY << "]" << std::endl;

					MapCoords* coord = new MapCoords(sourceX, sourceY, dX, dY);
					result.push_back(coord);
					file.ignore();
				}
			}

			file.close();

			return result;
		}

		Tile* GetTileAtPosition(SDL_Point point) {
			for (Tile* tile : tiles) {
				SDL_bool inside = SDL_PointInRect(&point, &tile->destination);
				if (inside == SDL_TRUE) {
					return tile;
				}
			}
			
			return NULL;
		}

		void Render() {
			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			for (int i = 0; i < gridSizeX; i++) {
				SDL_RenderDrawLine(renderer, 400, i * rectSize, width + 400, i * rectSize);
				SDL_RenderDrawLine(renderer, 400 + (i * rectSize), 0, 400 + (i * rectSize), height);
			}

			// draw each tile
			for (Tile* tile : tiles) {
				if (tile->IsSelected) {
					SDL_RenderCopyEx(renderer, sprite->texture, &tile->source, &tile->destination, 0.0f, NULL, SDL_FLIP_NONE);
				}
			}
		}
	
	};
}