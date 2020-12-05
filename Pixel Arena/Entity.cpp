#include "Entity.h"

Entity::Entity()
{

	this->x = 0.f;
	this->y = 0.f;
	this->vx = 0.f;
	this->vy = 0.f;
	this->DegAngle = 0;
	this->DegAngleTemp = DegAngle;


}

bool Entity::InView(sf::Vector2f View, double ViewAngle,double fov)
{
	bool ReturnValue = 0;

	//Calculate the Vector between View and 
	double dX = this->x - View.x;
	double dY = -(this->y - View.y);

	double AngletoEntity = LogManager::FixAngle(LogManager::RadtoDeg(std::atan2f(dY, dX)));
	double RightView = LogManager::FixAngle(ViewAngle - fov / 2.0);
	double LeftView = LogManager::FixAngle(ViewAngle + fov / 2.0);


	//Check if in View
	if (RightView < LeftView) {
		ReturnValue = RightView <= AngletoEntity && AngletoEntity <= LeftView;
		AngletoScreen = 1.0 - (AngletoEntity - RightView) / (LeftView - RightView);
	}
	else {
		if (RightView <= AngletoEntity) { // < 360 if crossing 360 line
			ReturnValue = true;
			LeftView = RightView + fov;
			AngletoScreen = 1.0 - (AngletoEntity - RightView) / (LeftView - RightView);//not sure

		}
		else if (AngletoEntity <= LeftView) { // > 0 if crossing 360 line
			ReturnValue = true;
			RightView = LeftView - fov;
			AngletoScreen = 1.0 - (AngletoEntity - RightView) / (LeftView - RightView);//not sure
		}	
	}

	//AngletoEntity vs entity view angle
	if (ReturnValue) {
		double radEntity = LogManager::DegtoRad(this->DegAngle);
		double radRotEntity = 0;//rotated entity angle as reference vector
		double radRotToEntity = LogManager::DegtoRad(AngletoEntity) - radEntity;
		//skip flipping due to -y in sfml
		double degAngleBetween = LogManager::RadtoDeg(atan2f(sin(radRotToEntity),cos(radRotToEntity)));

		int dPAVE = int(degAngleBetween + 180); // degPlayerAngleVsEntity


		//switch ranges are a GCC extension :/
		//will do ifs then

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

void Entity::Update(double distance)
{
	InternalClock.Count();
	this->distanceToPlayer = distance;
	AnimationState = int(InternalClock.rTotalTime() / AnimationSpeed) % 3;
}

sf::Vector2f Entity::getPosition() const
{
	return sf::Vector2f(x,y);
}

void Entity::drawEntity(double* Z_Buffer, sf::RenderTarget& target, sf::RenderStates states)
{
}

