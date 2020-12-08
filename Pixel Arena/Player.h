#pragma once
#include "Entity.h"
#include "LevelMap.h"
class Player : public Entity
{
public:
	Player(float x,float y,LevelMap* level);
	void Update(double fTime);
	void ForceActOnPlayer(float Fx, float Fy);
	void VectorPlayer(float Fx, float Fy,double fTime);
	void SetSprint(bool condition);

	void setHealth(float _Health);///< Sets Player Health
	float getHealth();///< Returns Player Health
private:
	float Health = 100.f;
	bool Sprint = 0;
	const float Acceleration = 10.f;
	const float MaxSpeed = 128.f;

	LevelMap* Level;
	void UpdatePosition(double fTime);
	void CapSpeed();
	void StopVel(float fTime);

};

