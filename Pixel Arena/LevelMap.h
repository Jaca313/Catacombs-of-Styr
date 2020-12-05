#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include "LogManager.h"
class LevelMap
{
private:
	LogManager& InfoTool = LogManager::getInstance();



public:
	const float TileSize = 64;
	LevelMap();
	void LoadLevel(std::wstring LevelName);
	char* Tiles;
	short MapX;
	short MapY;



private:
	int TextureCeiling;//make it load in constructor
	int TextureFloor;
public:
	int getTexCeil() const;
	int getTexFloor() const;
};

