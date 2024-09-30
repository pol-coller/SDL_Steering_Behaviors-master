#pragma once
#include "Agent.h"
#include "Obstacle.h"

class Seek :
	public Agent::SteeringBehavior
{
public:
	Seek();
	~Seek();
	Vector2D calculateSteeringForce(Agent *agent, float dtime);
};
