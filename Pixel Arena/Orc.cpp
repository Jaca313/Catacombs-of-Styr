#include "stdafx.h"
#include "Orc.h"

Orc::Orc(sf::Vector2f pos, int Texture)
{
	this->x = pos.x;
	this->y = pos.y;

	this->AnimationMap = Resources->getTex(Texture);

	Object.setTexture(AnimationMap);
	Object.setPosition(600.0,600.0);
	Object.setSize(sf::Vector2f(100, 100));

	AnimSizeX = AnimationMap->getSize().x / 3.0;
	AnimSizeY = AnimationMap->getSize().y / 4.0;
}

void Orc::drawEntity(double* Z_Buffer,sf::RenderTarget& target, sf::RenderStates states)
{
	UpdateAnimation(target,Z_Buffer);
	if(!m_bObscured)
		draw(target, states);
}

void Orc::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Resources->ClipEntity.setUniform("Z_Buffer", Resources->Z_BufferTex);
	float DistanceToPlayer = static_cast<float>(distanceToPlayer);
	Resources->ClipEntity.setUniform("distEntity", DistanceToPlayer);
	Resources->ClipEntity.setUniform("screenresolution", sf::Vector2f(target.getSize().x,target.getSize().y));
	Resources->ClipEntity.setUniform("obraz", sf::Shader::CurrentTexture);

	states.shader = &Resources->ClipEntity;
	target.draw(this->Object, states);


	//sf::Sprite ASD = sf::Sprite(*Object.getTexture());
	//target.draw(ASD,states);
}

void Orc::UpdateAnimation(sf::RenderTarget& target, double* Z_Buffer)
{
	Object.setTextureRect(sf::IntRect(sf::Vector2i(AnimationState * AnimSizeX, AnimSizeY * LookAngle), sf::Vector2i(AnimSizeX, AnimSizeY)));
	float m_winSizeX = target.getSize().x;
	float m_winSizeY = target.getSize().y;

	float Scale = (128.0 * m_winSizeY / 2) / this->distanceToPlayer;
	sf::Vector2f setSize = sf::Vector2f(Scale, 2 * Scale);
	Object.setSize(setSize);
	sf::Vector2f setOrigin = sf::Vector2f(Object.getSize().x / 2.0, Object.getSize().y);
	Object.setOrigin(setOrigin.x, setOrigin.y);

	//Not correct at distance but it will have to do
	//Object.setPosition(m_winSizeX * this->AngletoScreen, m_winSizeY / 2.0 +  Scale);



	//Looks ok
	m_dDistanceToProj = (target.getSize().x / 2.0) / tan(LogManager::DegtoRad(c_Fov / 2.0));// for fov(90)
	double NewAngle = LogManager::DegtoRad((AngletoScreen - 0.5) * 90);
	double xFinalPosition = m_winSizeX / 2.0 + tan(NewAngle) * m_dDistanceToProj;
	Object.setPosition(xFinalPosition, m_winSizeY / 2.0 + Scale);


	//Clipping Code just for reducing draw calls
	//int leftPos = int(xFinalPosition - Scale / 2.0) < 0 ? 0 : int(xFinalPosition - Scale / 2.0);
	//int centerleftPos = int(xFinalPosition - Scale / 4.0) < 0 ? 0 : int(xFinalPosition - Scale / 4.0);
	//int centerrightPos = int(xFinalPosition + Scale / 4.0) > m_winSizeX ? m_winSizeX : int(xFinalPosition + Scale / 4.0);
	//int rightPos = int(xFinalPosition + Scale / 2.0) > m_winSizeX ? m_winSizeX : int(xFinalPosition + Scale / 2.0);

	//bool leftObscured = Z_Buffer[leftPos] < this->distanceToPlayer;
	//bool centerLeftObscured = Z_Buffer[centerleftPos] < this->distanceToPlayer;
	//bool centerRightObscured = Z_Buffer[centerrightPos] < this->distanceToPlayer;
	//bool rightObscured = Z_Buffer[rightPos] < this->distanceToPlayer;

	//if (leftObscured && centerLeftObscured && centerRightObscured && rightObscured)m_bObscured = true;
	//else m_bObscured = false;


}
