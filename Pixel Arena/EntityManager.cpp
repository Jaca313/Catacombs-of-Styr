#include "stdafx.h"
#include "EntityManager.h"



std::vector<Entity*>* EntityManager::getEntities()
{
	//Returns Entities
	return &Entities;
}

void EntityManager::UpdateAll()
{
	//Updates Entities and sorts them back to front
	for (auto E : Entities) {
		E->Update(distanceFromPlayer(sf::Vector2f(Butcher->x,Butcher->y),*E));
		//std::sort(Entities.begin(), Entities.end(), [this](Entity O, Entity T) {return compareDistance(O, T); });
		std::sort(Entities.begin(), Entities.end(), std::bind(&EntityManager::compareDistance,this, std::placeholders::_1, std::placeholders::_2));
	}
}

void EntityManager::setPlayerPointer(Player* pPlayer)
{
	//Set pointer to Player (called from gamestate)
	this->Butcher = pPlayer;
}


bool EntityManager::compareDistance(Entity* O1, Entity* O2)
{
	//Returns Comparision between Entity distance from player
	return (O1->distanceToPlayer > O2->distanceToPlayer);
}

float EntityManager::distanceFromPlayer(sf::Vector2f pos,Entity Object)
{
	//Calculate Pythagorean Distance to Player
	float dX = pos.x - Object.getPosition().x;
	float dY = pos.y - Object.getPosition().y;
	return sqrtf(dX * dX + dY * dY);
}




