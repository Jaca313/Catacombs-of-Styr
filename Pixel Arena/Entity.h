#pragma once
#include <cmath>
#include "ResourceManager.h"
#include "Timer.h"
class Entity 
{
public:
	Entity();
public:
	float x,y; //Pos
	float vx,vy; // Mov Speed
	int DegAngle = 0;
	float DegAngleTemp = 0.f;

	ResourceManager* Resources = &ResourceManager::getInstance();

	sf::Texture* AnimationMap = nullptr;
	int AnimationState = 0;
	float AnimationSpeed = 1/3.f;

	int AnimationRotation = 0;
	bool InView(sf::Vector2f View, float ViewAngle, float fov);

	Timer InternalClock = Timer(1);

	void Update(float distance);

	sf::Vector2f getPosition() const;



	virtual void drawEntity(float* Z_Buffer,sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);


	float distanceToPlayer = FLT_MAX;
	float AngletoScreen = 0.0; // normalized is the measure of left to right screen span
	float m_dDistanceToProj = 0.0;// 
	//0 forward looking orc
	//1 left
	//2 right
	//3 back
	int LookAngle = 0;

	bool m_bObscured;
};

