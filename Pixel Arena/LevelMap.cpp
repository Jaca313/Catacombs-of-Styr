#include "LevelMap.h"

LevelMap::LevelMap()
{
	//Default Values
	MapX = 1;
	MapY = 1;
	Tiles = NULL;

}

void LevelMap::LoadLevel(std::wstring LevelName)
{
	std::ifstream ifs(LevelName);
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

int LevelMap::getTexCeil() const
{
	return this->TextureCeiling;
}

int LevelMap::getTexFloor() const
{
	return this->TextureFloor;
}
