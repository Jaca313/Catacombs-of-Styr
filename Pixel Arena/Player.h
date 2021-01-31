#pragma once
#include "Entity.h"
#include "LevelMap.h"
class Player : public Entity ///< Player Character from which camera originates
{
public:
	Player(float x,float y,LevelMap* level);///< Constructor with pos and access to level data

	void update(float fTime);///< Updates Player position & other properties

	void vectorPlayer(sf::Vector2f _dVec);///< Changes Player Movement Vector

	void setHealth(float _Health);///< Sets Player Health
	float getHealth();///< Returns Player Health

	void setSprint(bool _condition);///< sets bool Sprint (changes Player speed)

	void tryOpenDoor();///< Try to open door in front
private:
	float m_fHealth = 100.f;///< Current player health
	bool m_bSprint = 0;///< Is player sprinting
	const float MaxSpeed = 128.f;///< Max Speed of Player
	const float SprintSpeed = 100.f;///< Cumulative! Adds sprint speed

	LevelMap* Level;///< access to level data

	void UpdatePosition();///< Player movement and collision
};

