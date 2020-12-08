#include "LevelMap.h"

const short LevelMap::getMapX() const
{
	return MapX;
}

const short LevelMap::getMapY() const
{
	return MapY;
}

const int LevelMap::getTileSize() const
{
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
	//Cleanup
	if(Tiles)free(Tiles);
}

void LevelMap::LoadLevel(std::wstring _LevelName)
{
	if (Tiles)free(Tiles);//Make sure we let go of the current memory
	std::ifstream ifs(_LevelName);
	std::string line;
	if (ifs){
		ifs >> MapX >> MapY >> TextureCeiling >> TextureFloor;
		Tiles = (char*)calloc((MapX * MapY + 1), sizeof(char));
		if (Tiles) {
			for (int i = 0; i < MapY; ++i)
				ifs >> &Tiles[i * MapX];
		}
		else InfoTool.ERR(4, "Tiles mem error");

	}
	else InfoTool.ERR(4, "NO MAP");


}

const int LevelMap::getTexCeil() const
{
	return this->TextureCeiling;
}

const int LevelMap::getTexFloor() const
{
	return this->TextureFloor;
}

char LevelMap::getTile(int _X) const
{
	if(_X < (MapX * MapY))return Tiles[_X];
	else return '.';
}
