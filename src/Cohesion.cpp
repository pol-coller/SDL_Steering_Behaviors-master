#include "Cohesion.h"

Cohesion::Cohesion()
{

}

Cohesion::~Cohesion()
{

}

Vector2D Cohesion::calculateSteeringForce(Agent* agent, float dtime)
{
	//Fer struct distance pel switch?
	//Definir near, medium, far distance a la clase chesion?
	//comparar la distancia (modul) de agent a center.

	//switch ()
	//{
	//	case
	//default:
	//	break;
	//}

	
	//Chesion
	Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForceChoesion = desiredVelocity - agent->getVelocity();
	steeringForceChoesion.Normalize();

	//S
	//desiredVelocity = agent->getCenterPosition() - agent->getPosition();
	//desiredVelocity.Normalize();
	//desiredVelocity *= agent->getMaxVelocity();
	//Vector2D steeringForceFlee = desiredVelocity - agent->getVelocity();
	//steeringForceFlee.Normalize();


	return (steeringForceChoesion * agent->getMaxForce()); //+ (steeringForceFlee * agent->getMaxForce());


}
