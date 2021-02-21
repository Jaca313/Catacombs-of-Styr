#pragma once
#include "Entity.h"
#include "Player.h"
#include "Orc.h"
#include <vector>
class EntityManager ///< Manages Entites in App
{
private:
	LogManager& InfoTool = LogManager::getInstance();
	//TODO: Load Entities from Save/Level Data File (posibbly separate from level data, different ext etc.)
	//HACK: Push some test orcs
	EntityManager() {///<Inline Constructor (pushes entites currently)
		//Entities.push_back(new Orc(sf::Vector2f(80, 80), 30));
		//Entities.push_back(new Orc(sf::Vector2f(34*64, 6*64), 33));
		//Entities.push_back(new Orc(sf::Vector2f(25 * 64, 4 * 64), 34));
		//Entities.push_back(new Orc(sf::Vector2f(3 * 64, 50 * 64), 37));
		//Entities.push_back(new Orc(sf::Vector2f(30 * 64, 2 * 64), 38));
		//Entities.push_back(new Orc(sf::Vector2f(150, 150), 41));
		//Entities.push_back(new Orc(sf::Vector2f(10 * 64, 3 * 64), 42));
		//Entities.push_back(new Orc(sf::Vector2f(30 * 64, 30 * 64), 43));
	}
	~EntityManager() {///<Empty Destructor

	}
public:
	///<Singleton implementation
	static EntityManager& getInstance() {
		static EntityManager theInstance;
		return theInstance;
	}

private:
	//sort them by distance
	std::vector<Entity*> Entities;///< Entity BaseClass List (player not included)
	Player* Butcher = nullptr;///< PLayer Pointer
	float distanceFromPlayer(sf::Vector2f pos, Entity Object);///,Calculates Entity distance relative to player(scaling mostly)

public:
	//TODO: Hide it better
	std::vector<Entity*>* getEntities();///<Returns Entity List Directly
	void UpdateAll();///<Updates Entities going through list

	void setPlayerPointer(Player* pPlayer);///<Gets Player pointer from current state(called in gamestate)
public:
	//sort backwards
	bool compareDistance(Entity* O1,Entity* O2);///<Sorts Entities Back to Front for drawing Purposes



};

