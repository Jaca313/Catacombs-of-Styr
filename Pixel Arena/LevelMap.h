#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include "LogManager.h"

/** Binary Map Cell */
struct MapCell {
	bool wall = false; ///< is it to be rendered as a wall
	int id[6];///< Wall Texture index for faces
	bool door = false; // isDoor

};
struct Cell ///< Cube with Face info (Editor)
{ 
	bool wall = false;///< Is it to be rendered as a wall
	int id[6];///< Individual Face info (not currently used in full)
};

enum Face {///< Face enumerators for Cubes (editor)
	Floor = 0,///<Floor
	Top,///< Ceiling
	North,///<-y
	South,///<+y
	West,///<+x
	East///<-x
};

class LevelMap ///< LevelMap contains Level Data (Tile Map)
{
public:
	LevelMap();///<Default Constructor
	~LevelMap();///< Destructor - Cleans up Tiles and Cells pointers
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

	MapCell* MapData;
	MapCell	NullMapCell;
	//TODO: Switch every system to Cells
	//Prepare for multiface Walls and multitile Ceilings and floor
	Cell* Cells;///<Used in Editor /equivalent of Tiles
	Cell NullCell;///<Used in Editor /equivalent of Tiles
	void CreateCells();///<Used in Editor /loads Cells from Tiles
public:
	const short getMapX() const;///< Returns Map X size
	const short getMapY() const;///< Returns Map Y size
	const float getTileSize() const;///< Returns Map TileSize
	const int getTexCeil() const;///< Returns Ceiling Texture number
	const int getTexFloor() const;///< Returns Floor Texture number
	char getTile(int _X) const;///< Returns Tile at X
	char getTile(int _X,int _Y) const;///< Returns Tile at X

	Cell& getCell(int _X);///< Returns Cell at X position in array
	Cell& getCell(int _X,int _Y);///< Returns Cell at XY position
	Cell* editCell(int _X);///< Returns Cell pointer at X position in array (deprecated)

	void SaveFromCells(std::wstring _LevelName);///< Overwrites LevelData from Editor Cell Data

	/**
	 * Saves Map Data (MapCells) to File.
	 * 
	 * @param levelName File to be saved to
	 */
	void BinarySaveData(std::wstring levelName);

	/**
	 * Loads Map Data (MapCells) from File
	 * 
	 * @param levelName File to be loaded from
	 */
	void BinaryLoadData(std::wstring levelName);

	/**
	 * Create Empty Map 
	 * 
	 * @param sizeY SizeY of new Empty Map
	 * @param sizeX SizeX of new Empty Map
	 */
	void CreateEmptyMap(short sizeY, short sizeX);

	/**
	 * Return Reference to MapCell (2D Array)
	 * 
	 * @param x X position of MapCell to be retrieved
	 * @param y XY position of MapCell to be retrieved
	 * @return Reference to MapCell
	 */
	MapCell& getMapCell(int x, int y);

	/**
	* Return Reference to MapCell (1D Array)
	*
	* @param x X position in 1D Array of MapCell to be retrieved
	* @return Reference to MapCell
	*/
	MapCell& getMapCell(int x);

	/**
	 * Try to open Door on Map
	 * 
	 * @param x X position in 1D Array of Map
	 * @return if opened door
	 */
	bool openDoor(int x);

	/**
	 * Try to open Door on Map
	 * 
	 * @param x X position in 2D Array of Map
	 * @param y Y position in 2D Array of Map
	 * @return if opened door
	 */
	bool openDoor(int x, int y);


};

   