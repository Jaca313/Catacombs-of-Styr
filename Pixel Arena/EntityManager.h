#pragma once
#include "Entity.h"
#include "Player.h"
#include "Orc.h"
#include <vector>
class EntityManager 
{
private:
	LogManager& InfoTool = LogManager::getInstance();

	EntityManager() {
		Entities.push_back(new Orc(sf::Vector2f(80, 80), 30));
		Entities.push_back(new Orc(sf::Vector2f(34*64, 6*64), 33));
		Entities.push_back(new Orc(sf::Vector2f(25 * 64, 4 * 64), 34));
		Entities.push_back(new Orc(sf::Vector2f(3 * 64, 50 * 64), 37));
		Entities.push_back(new Orc(sf::Vector2f(30 * 64, 2 * 64), 38));
		Entities.push_back(new Orc(sf::Vector2f(150, 150), 41));
		Entities.push_back(new Orc(sf::Vector2f(10 * 64, 3 * 64), 42));
		Entities.push_back(new Orc(sf::Vector2f(30 * 64, 30 * 64), 43));
	}
	~EntityManager() {

	}
public:
	static EntityManager& getInstance() {
		static EntityManager theInstance;
		return theInstance;
	}

private:
	//sort them by distance
	std::vector<Entity*> Entities;
	Player* Butcher = nullptr;
	float distanceFromPlayer(sf::Vector2f pos, Entity Object);

public:
	std::vector<Entity*>* getEntities();
	void UpdateAll();

	void setPlayerPointer(Player* pPlayer);
public:
	//sort backwards
	bool compareDistance(Entity* O1,Entity* O2);



};

