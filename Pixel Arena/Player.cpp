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

void Player::Update(double fTime)
{
	UpdatePosition(fTime);
}

void Player::ForceActOnPlayer(float Fx, float Fy)
{
	this->vx += Fx;
	this->vy += Fy;
}

void Player::VectorPlayer(float Fx, float Fy, double fTime)
{
	this->vx += Fx * fTime;
	this->vy += Fy * fTime;
}

void Player::SetSprint(bool condition)
{
	this->Sprint = condition;
}

void Player::setHealth(float _Health)
{
	float fixedHealth = _Health > 100.f ? 100.f : _Health;
	fixedHealth = fixedHealth < 0.f ? 0.f : fixedHealth;
	this->Health = fixedHealth;
}

float Player::getHealth()
{
	return this->Health;
}

void Player::UpdatePosition(double fTime)
{
	CapSpeed();
	float dx = vx * (MaxSpeed + 100.f * Sprint);
	float dy = vy * (MaxSpeed + 100.f * Sprint);

	//Enables Collision and Wall sliding
	int TileX = (x + dx) / (float)Level->TileSize;//Player Will be there if we move
	int TileY = (y + dy) / (float)Level->TileSize;

	int TileX2 = (x) / (float)Level->TileSize;//Player Is now there
	int TileY2 = (y) / (float)Level->TileSize;

	int C1 = Level->Tiles[TileX + Level->MapX * TileY2];
	int C2 = Level->Tiles[TileX2 + Level->MapX * TileY];
	if (C1 < '0' || C1 >'9')
		this->x += dx;
	if (C2 < '0' || C2 > '9')
		this->y += dy;

	StopVel(fTime);
}

void Player::CapSpeed()
{
	float factor = sqrt(vx * vx + vy * vy)/1.f;
	if (factor > 1.f) {
		vx /= factor;
		vy /= factor;
	}


}

void Player::StopVel(float fTime)
{
	if(abs(vx) > 0.f)vx += -vx * fTime * 100;//tenth of a second to stop
	if (abs(vx) > 0.f)vy += -vy * fTime * 100;//tenth of a second to stop
}
