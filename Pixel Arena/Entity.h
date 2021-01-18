#pragma once
#include <cmath>
#include "ResourceManager.h"
#include "Timer.h"
class Entity 
{
public:
	Entity();
public:
	float x,y;///< Position of Entity
	float vx,vy;///< Vector of Movement
	int DegAngle = 0;///< Current Heading
	float DegAngleTemp = 0.f;///< Helper variable of Heading

	ResourceManager* Resources = &ResourceManager::getInstance();///< Access to Resource Manager

	sf::Texture* AnimationMap = nullptr;///< SpriteMap of Entity
	int AnimationState = 0;///< Current Animation Sprite
	float AnimationSpeed = 1/3.f;///< Speed of Animation (lower is faster)

	int AnimationRotation = 0;///< Current Animation Rotation relative to player
	bool InView(sf::Vector2f View, float ViewAngle, float fov);///< Check if on Screen

	Timer InternalClock = Timer(1);///< Animation Timer mostly

	void Update(float distance);///< Updates Internal State of Entity

	sf::Vector2f getPosition() const;///< Returns Position

	virtual void drawEntity(float* Z_Buffer,sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);///< Draws Entity


	float distanceToPlayer = FLT_MAX;///< Current Distance to Plater
	float AngletoScreen = 0.0;///< normalized is the measure of left to right screen span
	float m_dDistanceToProj = 0.0;///< 
	//0 forward looking orc
	//1 left
	//2 right
	//3 back
	int LookAngle = 0;///< Current Animation Rotation relative to player

	bool m_bObscured;///< if obscured behind wall /CPU computation(currently not used)
};

