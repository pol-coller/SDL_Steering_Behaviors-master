#pragma once
#include "Agent.h"
class Wander :
	public Agent::SteeringBehavior
{
private:
	const float radius, offset, maxAngle;
	float WanderAngle;
	float RandomBinomial();


public:
	Wander();
	~Wander();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);


	//	Set/get vars
};

