#include "Player.h"

Player::Player(float x, float y, LevelMap* level)
{
	//Init position, speed and rotation
	this->x = x;
	this->y = y;
	this->vx = 0.f;
	this->vy = 0.f;
	this->DegAngle = 0;
	this->DegAngleTemp = (float)DegAngle;

	//Bind Level access
	this->Level = level;
}

void Player::update(float fTime)
{
	//Update Movement
	UpdatePosition();
}

void Player::vectorPlayer(sf::Vector2f _dVec)
{
	//Force player movement vector
	this->vx += _dVec.x;
	this->vy += _dVec.y;
}

void Player::setSprint(bool _condition)
{
	//Sets player sprint
	this->m_bSprint = _condition;
}

void Player::tryOpenDoor()
{
	//Get Player map tile position
	int realX = int(x / 64.0);
	int realY = int(y / 64.0);

	//Check which tile(Door next to player) Player is trying to Open and try it
	if (DegAngle < 45 && DegAngle >= 0 || DegAngle < 360 && DegAngle >= 315)Level->openDoor(realX + 1 + realY * Level->getMapX());//right
	else if (DegAngle >= 45 && DegAngle < 135)Level->openDoor(realX + (realY - 1) * Level->getMapX());//up
	else if (DegAngle >= 135 && DegAngle < 225)Level->openDoor(realX - 1 + realY * Level->getMapX());//left
	else if (DegAngle >= 225 && DegAngle < 315)Level->openDoor(realX + (realY + 1) * Level->getMapX());//down
}

void Player::setHealth(float _Health)
{
	//Force updated Health between 0-100
	float fixedHealth = _Health > 100.f ? 100.f : _Health;
	fixedHealth = fixedHealth < 0.f ? 0.f : fixedHealth;

	//Set updated Health
	this->m_fHealth = fixedHealth;
}

float Player::getHealth()
{
	//Returns actual Player Health
	return this->m_fHealth;
}

void Player::UpdatePosition()
{
	//Get Movement Angle (in Rad)
	float HeadingVector = atan2f(vy, vx);
	//Get Movement Vector of Magnitude 2 in direction of Travel
	float Ox = 2.f*cos(HeadingVector);
	float Oy = 2.f*sin(HeadingVector);

	//Get Vector of Change of Position with Player Speed
	float dx = vx * (MaxSpeed + SprintSpeed * m_bSprint);
	float dy = vy * (MaxSpeed + SprintSpeed * m_bSprint);

	//Enables Collision and Wall sliding
	int TileX = int((x + dx + Ox) / (float)Level->getTileSize());//Player Will be there if we move
	int TileY = int((y + dy + Oy) / (float)Level->getTileSize());

	int TileX2 = int((x) / (float)Level->getTileSize());//Player Is now there
	int TileY2 = int((y) / (float)Level->getTileSize());

	//Get tiles to be moved to
	auto& C1 = Level->getMapCell(TileX,TileY2);
	auto& C2 = Level->getMapCell(TileX2,TileY);

	//Check if future tiles are walls
	if (!C1.wall)
		this->x += dx;
	if (!C2.wall)
		this->y += dy;

	//Slows down player (fps dependent / fps are clamped)
	this->vx /= 1.8f;
	this->vy /= 1.8f;
}


