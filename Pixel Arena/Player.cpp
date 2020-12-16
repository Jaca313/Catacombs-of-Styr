#include "Player.h"

Player::Player(float x, float y, LevelMap* level)
{
	this->x = x;
	this->y = y;
	this->vx = 0.f;
	this->vy = 0.f;
	this->DegAngle = 0;
	this->DegAngleTemp = (float)DegAngle;

	this->Level = level;
}

void Player::update(float fTime)
{
	UpdatePosition();
}

void Player::vectorPlayer(sf::Vector2f _dVec)
{
	this->vx += _dVec.x;
	this->vy += _dVec.y;
}

void Player::setSprint(bool _condition)
{
	this->m_bSprint = _condition;
}

void Player::tryOpenDoor()
{
	int realX = int(x / 64.0);
	int realY = int(y / 64.0);
	if (DegAngle < 45 && DegAngle >= 0 || DegAngle < 360 && DegAngle >= 315)Level->openDoor(realX + 1 + realY * Level->getMapX());//right
	else if (DegAngle >= 45 && DegAngle < 135)Level->openDoor(realX + (realY - 1) * Level->getMapX());//up
	else if (DegAngle >= 135 && DegAngle < 225)Level->openDoor(realX - 1 + realY * Level->getMapX());//left
	else if (DegAngle >= 225 && DegAngle < 315)Level->openDoor(realX + (realY + 1) * Level->getMapX());//down
}

void Player::setHealth(float _Health)
{
	float fixedHealth = _Health > 100.f ? 100.f : _Health;
	fixedHealth = fixedHealth < 0.f ? 0.f : fixedHealth;
	this->m_fHealth = fixedHealth;
}

float Player::getHealth()
{
	return this->m_fHealth;
}

void Player::UpdatePosition()
{

	float dx = vx * (MaxSpeed + SprintSpeed * m_bSprint);
	float dy = vy * (MaxSpeed + SprintSpeed * m_bSprint);

	//Enables Collision and Wall sliding
	int TileX = int((x + dx) / (float)Level->getTileSize());//Player Will be there if we move
	int TileY = int((y + dy) / (float)Level->getTileSize());

	int TileX2 = int((x) / (float)Level->getTileSize());//Player Is now there
	int TileY2 = int((y) / (float)Level->getTileSize());

	int C1 = Level->getTile(TileX + Level->getMapX() * TileY2);
	int C2 = Level->getTile(TileX2 + Level->getMapX() * TileY);
	if (C1 < '0' || C1 >'9')
		this->x += dx;
	if (C2 < '0' || C2 > '9')
		this->y += dy;

	this->vx /= 1.8f;
	this->vy /= 1.8f;

}


