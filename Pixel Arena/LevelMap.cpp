#include "LevelMap.h"

void LevelMap::CreateCells()
{

	if (Cells)delete[] Cells;
	Cells = new Cell[MapX * MapY];

	//Default
	for (int i = 0; i < MapX * MapY; i++) {
		Cells[i].wall = false;
		Cells[i].id[Face::Floor] = TextureFloor;
		Cells[i].id[Face::Top] = TextureCeiling;
		Cells[i].id[Face::North] = 1;
		Cells[i].id[Face::South] = 1;
		Cells[i].id[Face::West] = 1;
		Cells[i].id[Face::East] = 1;
	}

	for (int y = 0; y < MapY; y++) {
		for (int x = 0; x < MapX ; x++) {
			if (getTile(x, y) != '.') {
				this->getCell(x, y).wall = true;
				this->getCell(x, y).id[Face::North] = getTile(x, y) - '0';
				this->getCell(x, y).id[Face::South] = getTile(x, y) - '0';
				this->getCell(x, y).id[Face::West] = getTile(x, y) - '0';
				this->getCell(x, y).id[Face::East] = getTile(x, y) - '0';
			}
		}
	}
}

const short LevelMap::getMapX() const
{
	//Returns Map Size (X)
	return MapX; 
}

const short LevelMap::getMapY() const
{
	//Returns Map Size (Y)
	return MapY;
}

const float LevelMap::getTileSize() const
{
	//Returns constant TileSize (64)
	return TileSize;
}

LevelMap::LevelMap()
{
	//Default Values
	MapX = 1;
	MapY = 1;
	Tiles = NULL;
	TextureCeiling = 0;
	TextureFloor = 0;
}

LevelMap::~LevelMap()
{
	//Cleanup Tiles and Cells pointers to 2D arrays
	if(Tiles)free(Tiles);
	if (Cells)delete[] Cells;
}

void LevelMap::LoadLevel(std::wstring _LevelName)
{
	if (Tiles)free(Tiles);//Make sure we let go of the current memory
	
	//Get Path to Level File
	std::wstring Path = L"Levels\\" + _LevelName;
	std::ifstream ifs(Path);


	//Load Map from file
	if (ifs){
		ifs >> MapX >> MapY >> TextureCeiling >> TextureFloor; //Load Size of Map and Textures of Floor and Ceiling
		Tiles = (char*)calloc((MapX * MapY + 1), sizeof(char));
		if (Tiles) {
			for (int i = 0; i < MapY; ++i)
				ifs >> &Tiles[i * MapX];
		}
		else InfoTool.ERR(4, "Tiles mem error");

	}
	else InfoTool.ERR(4, "NO MAP");

	//Init Cells for Editor
	CreateCells();
}

const int LevelMap::getTexCeil() const
{
	//Return Currently Used Ceiling Texture
	return this->TextureCeiling;
}

const int LevelMap::getTexFloor() const
{
	//Return Currently Used Floor Texture
	return this->TextureFloor;
}

char LevelMap::getTile(int _X) const
{
	//Get Tile Char Bound by Map Size (X position in 1D array)
	if(_X < (MapX * MapY) && _X >= 0)return Tiles[_X];
	else return '.';
}

char LevelMap::getTile(int _X, int _Y) const
{
	//Get Tile Char Bound by Map Size (XY position in 2D array)
	if (_X < 0 || _Y < 0)return '.';
	if (_X < MapX && _Y < MapY)return Tiles[_Y * MapX + _X];
	else return '.';

}

bool LevelMap::openDoor(int _X)
{
	//Check if on map and if door('0') if then remove the door
 	if (_X < (MapX * MapY)) {
		if (Tiles[_X] == '0') {
			Tiles[_X] = '.';
			return true;
		}
		else return false;
	}
	else return false;

}

Cell& LevelMap::getCell(int _X)
{
	//Get Cell Bound by Map Size (X position in 1D array)
	if (_X >= 0 && _X < MapX * MapY)
		return Cells[_X];
	else return NullCell;
}

Cell& LevelMap::getCell(int _X, int _Y)
{
	//Get Cell Bound by Map Size (XY position in 2D array)
	if (_X >= 0 && _X < MapX * MapY)
		return Cells[_Y * MapX + _X];
	else return NullCell;
}

Cell* LevelMap::editCell(int _X)
{
	//Get Cell pointer Bound by Map Size (X position in 1D array)
	if (_X >= 0 && _X < MapX * MapY)
		return &Cells[_X];
	else return &NullCell;
}

void LevelMap::SaveFromCells(std::wstring _LevelName)
{
	//Get Level Path from fileName
	std::wstring Path = L"Levels\\" + _LevelName;
	std::ofstream ifs(Path);

	//Write Level Data to File
	if (ifs) {
		ifs << MapX << " " << MapY  << " "<< TextureCeiling << " " << TextureFloor << "\n";

		for (int i = 0; i < MapY; i++) {
			for (int p = 0; p < MapX; p++) {
				if (getCell(p, i).wall)
					ifs << char(getCell(p, i).id[Face::North] + '0');
				else ifs << '.';

			}
			ifs << "\n";
		}

	}
	else InfoTool.ERR(4, "NO MAP");
}
