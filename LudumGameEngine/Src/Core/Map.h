#pragma once
#include <string>

class Map {
private:
	std::string textureId;
	int scale;
	int tileSize;
public:

	Map(std::string textureId, int scale, int size);
	~Map();

	void LoadMap(std::string filePah, int mapSizeX, int mapSizeY);
	void AddTile(int sourceX, int sourceY, int x, int y);
};