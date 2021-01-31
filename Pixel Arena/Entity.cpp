#include "Entity.h"

Entity::Entity()
{
	//Default Initialization
	this->x = 0.f;
	this->y = 0.f;
	this->vx = 0.f;
	this->vy = 0.f;
	this->DegAngle = 0;
	this->DegAngleTemp = (float)DegAngle;
}

bool Entity::InView(sf::Vector2f View, float ViewAngle, float fov)
{
	bool ReturnValue = 0;

	//Calculate the Vector between View and Entity
	float dX = this->x - View.x;
	float dY = -(this->y - View.y);

	//Get Angle of Vector between View and Entity
	float AngletoEntity = LogManager::FixAngle(LogManager::RadtoDeg(std::atan2f(dY, dX)));

	//Get Right and Left Bounds of View (in Deg)
	float RightView = LogManager::FixAngle(ViewAngle - fov / 2.f);
	float LeftView = LogManager::FixAngle(ViewAngle + fov / 2.f);


	//Check if Entity in View (on Screen)
	if (RightView < LeftView) {
		ReturnValue = RightView <= AngletoEntity && AngletoEntity <= LeftView;
		AngletoScreen = 1.f - (AngletoEntity - RightView) / (LeftView - RightView);
	}
	else {
		if (RightView <= AngletoEntity) { // < 360 if crossing 360 line
			ReturnValue = true;
			LeftView = RightView + fov;
			AngletoScreen = 1.f - (AngletoEntity - RightView) / (LeftView - RightView);//not sure

		}
		else if (AngletoEntity <= LeftView) { // > 0 if crossing 360 line
			ReturnValue = true;
			RightView = LeftView - fov;
			AngletoScreen = 1.f - (AngletoEntity - RightView) / (LeftView - RightView);//not sure
		}	
	}

	//AngletoEntity vs entity view angle
	if (ReturnValue) {
		float radEntity = LogManager::DegtoRad((float)this->DegAngle);
		float radRotEntity = 0;//rotated entity angle as reference vector
		float radRotToEntity = LogManager::DegtoRad(AngletoEntity) - radEntity;
		//skip flipping due to -y in sfml
		float degAngleBetween = LogManager::RadtoDeg(atan2f(sin(radRotToEntity),cos(radRotToEntity)));

		//Angle of Entity compared to vector between it and View
		int dPAVE = int(degAngleBetween + 180); // degPlayerAngleVsEntity


		//switch ranges are a GCC extension :/
		//will do ifs then


		//Decide what angle the Entity is rotated compared to Screen
		if (dPAVE > 45 && dPAVE < 135)//left
			LookAngle = 1;
		else if (dPAVE >= 135 && dPAVE <= 225)//back 
			LookAngle = 3;
		else if (dPAVE > 225 && dPAVE < 315)//right
			LookAngle = 2;
		else if ((dPAVE >= 315 && dPAVE <= 360) || (dPAVE > 0 && dPAVE <= 45))//front
			LookAngle = 0;

	}

	return ReturnValue;
}

void Entity::Update(float distance)
{
	InternalClock.Count();//Get internal elapsed time
	this->distanceToPlayer = distance;//update distance to player camera for scaling
	AnimationState = int(InternalClock.rTotalTime() / AnimationSpeed) % 3;//update animations
}

sf::Vector2f Entity::getPosition() const
{
	return sf::Vector2f(x,y);
}

void Entity::drawEntity(float* Z_Buffer, sf::RenderTarget& target, sf::RenderStates states)
{
}

