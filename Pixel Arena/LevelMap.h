#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include "LogManager.h"
struct Cell {
	bool wall = false;
	int id[6];
};

enum Face {
	Floor = 0,
	Top,
	North,
	South,
	West,
	East
};

class LevelMap
{
public:
	LevelMap();
	~LevelMap();
private:
	LogManager& InfoTool = LogManager::getInstance();///< Access to Internal Messages
public:
	void LoadLevel(std::wstring _LevelName);///< Load Level Data from File

private:
	//Map properties
	short MapX;///<Map size
	short MapY;///<Map Size
	int TextureCeiling;///< Texture used in Ceiling
	int TextureFloor;///< Texture used in Floor
	char* Tiles;///< Direct pointer
	const float TileSize = 64;///< Tile Size map to world pos

	Cell* Cells;
	Cell NullCell;
	void CreateCells();
public:
	const short getMapX() const;///< Returns Map X size
	const short getMapY() const;///< Returns Map Y size
	const float getTileSize() const;///< Returns Map TileSize
	const int getTexCeil() const;///< Returns Ceiling Texture number
	const int getTexFloor() const;///< Returns Floor Texture number
	char getTile(int _X) const;///< Returns Tile at X
	char getTile(int _X,int _Y) const;///< Returns Tile at X
	bool openDoor(int _X);///< removes door from map

	Cell& getCell(int _X);
	Cell& getCell(int _X,int _Y);
	Cell* editCell(int _X);
};

   