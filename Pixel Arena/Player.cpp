#include "Player.h"

Player::Player(float x, float y, LevelMap* level)
{
	this->x = x;
	this->y = y;
	this->vx = 0.f;
	this->vy = 0.f;
	this->DegAngle = 0;
	this->DegAngleTemp = DegAngle;

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
	//CapSpeed();
	float dx = vx * (MaxSpeed + SprintSpeed * m_bSprint);
	float dy = vy * (MaxSpeed + SprintSpeed * m_bSprint);

	//Enables Collision and Wall sliding
	int TileX = (x + dx) / (float)Level->getTileSize();//Player Will be there if we move
	int TileY = (y + dy) / (float)Level->getTileSize();

	int TileX2 = (x) / (float)Level->getTileSize();//Player Is now there
	int TileY2 = (y) / (float)Level->getTileSize();

	int C1 = Level->getTile(TileX + Level->getMapX() * TileY2);
	int C2 = Level->getTile(TileX2 + Level->getMapX() * TileY);
	if (C1 < '0' || C1 >'9')
		this->x += dx;
	if (C2 < '0' || C2 > '9')
		this->y += dy;

	this->vx /= 1.8f;
	this->vy /= 1.8f;

}


