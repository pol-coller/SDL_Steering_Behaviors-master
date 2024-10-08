#pragma once
#include "Agent.h"

class Alignment : public Agent::SteeringBehavior
{
private:
	float const neighbourMaxDistance;
public:
	Alignment();
	~Alignment();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};

