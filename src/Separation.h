#pragma once
#include "Agent.h"
#include "Vector2D.h"

class Separation : public Agent::SteeringBehavior
{
private:
	float const maxDistance;
public:
	Separation();
	~Separation();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};

