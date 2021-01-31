#include "stdafx.h"
#include "Orc.h"

Orc::Orc(sf::Vector2f pos, int Texture)
{
	//Init position
	this->x = pos.x;
	this->y = pos.y;

	//Get Spritesheet
	this->AnimationMap = Resources->getTex(Texture);

	//Setup Sprite
	Object.setTexture(AnimationMap);
	Object.setPosition(600.f,600.f);
	Object.setSize(sf::Vector2f(100.f, 100.f));

	//Setup Animation Sprite Size
	AnimSizeX = int(AnimationMap->getSize().x / 3.f);
	AnimSizeY = int(AnimationMap->getSize().y / 4.f);
}

void Orc::drawEntity(float* Z_Buffer,sf::RenderTarget& target, sf::RenderStates states)
{
	UpdateAnimation(target,Z_Buffer);//Update Sprite
	if(!m_bObscured)//Check if Obscured by wall(currently unused due to GPU processing)
		draw(target, states);
}

void Orc::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Set Shader uniforms
	Resources->ClipEntity.setUniform("Z_Buffer", Resources->Z_BufferTex);
	float DistanceToPlayer = static_cast<float>(distanceToPlayer);
	Resources->ClipEntity.setUniform("distEntity", DistanceToPlayer);
	Resources->ClipEntity.setUniform("screenresolution", sf::Vector2f(target.getSize().x,target.getSize().y));
	Resources->ClipEntity.setUniform("obraz", sf::Shader::CurrentTexture);

	//Bind Shader
	states.shader = &Resources->ClipEntity;
	target.draw(this->Object, states);//draw


	//sf::Sprite ASD = sf::Sprite(*Object.getTexture());
	//target.draw(ASD,states);
}

void Orc::UpdateAnimation(sf::RenderTarget& target, float* Z_Buffer)
{
	//Updates Sprite from Spritesheet
	Object.setTextureRect(sf::IntRect(sf::Vector2i(AnimationState * AnimSizeX, AnimSizeY * LookAngle), sf::Vector2i(AnimSizeX, AnimSizeY)));
	
	//Get window Size
	float m_winSizeX = float(target.getSize().x);
	float m_winSizeY = float(target.getSize().y);

	//Set Scaling, and origin after scaling
	float Scale = (128.f * m_winSizeY / 2) / this->distanceToPlayer;
	sf::Vector2f setSize = sf::Vector2f(Scale, 2 * Scale);
	Object.setSize(setSize);
	sf::Vector2f setOrigin = sf::Vector2f(Object.getSize().x / 2.f, Object.getSize().y);
	Object.setOrigin(setOrigin.x, setOrigin.y);

	//Not correct at distance but it will have to do
	//Object.setPosition(m_winSizeX * this->AngletoScreen, m_winSizeY / 2.0 +  Scale);



	//Looks ok
	//Get Position of Sprite on screen due to projection (Y not considered) 
	m_dDistanceToProj = (target.getSize().x / 2.f) / tan(LogManager::DegtoRad(c_Fov / 2.f));// for fov(90)
	float NewAngle = LogManager::DegtoRad((AngletoScreen - 0.5f) * 90);
	float xFinalPosition = m_winSizeX / 2.f + tan(NewAngle) * m_dDistanceToProj;
	Object.setPosition(xFinalPosition, m_winSizeY / 2.f + Scale);


	//Clipping Code just for reducing draw calls (GPU processing now)
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
