#include "Wander.h"

Wander::Wander() : offset(300.f), radius(50.f), maxAngle(0.45f), WanderAngle(0.0f)
{
	//srand(time(NULL));
}

Wander::~Wander()
{

}


Vector2D Wander::calculateSteeringForce(Agent* agent, float dt)
{

	WanderAngle += RandomBinomial() * maxAngle;

	float targetAngle = agent->getOrientation() + WanderAngle;

	Vector2D TargetPosition;
	Vector2D CircleCenter = agent->getPosition() + agent->getVelocity().Normalize() * offset;
	TargetPosition.x = CircleCenter.x + radius *cos(targetAngle);
	TargetPosition.y = CircleCenter.y + radius *sin(targetAngle);

	//DRAW CIRCLES
	draw_circle(TheApp::Instance()->getRenderer(), (int)CircleCenter.x, (int)CircleCenter.y, radius, 255, 255, 255, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)TargetPosition.x, (int)TargetPosition.y, 15, 0, 0, 255, 255);


							//el target sera el punt de la circumferencia
	Vector2D desiredVelocity = TargetPosition - agent->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce.Normalize();
	return steeringForce * agent->getMaxForce();
}

float Wander::RandomBinomial()
{
	
	float a = (double)rand() / ((double)RAND_MAX);
	float b = (double)rand() / ((double)RAND_MAX);
	return a - b;
	//return ((double)rand() / ((double)RAND_MAX)) - ((double)rand() / ((double)RAND_MAX));  // 1 | -1
		
}
