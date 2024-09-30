#pragma once
#include "Agent.h"
#include "Alignment.h"
#include "Cohesion.h"
#include "Separation.h"
#include "Seek.h"

class WeightedBlending : public Agent::SteeringBehavior
{
public:
	WeightedBlending();
	~WeightedBlending();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);

private:
	SteeringBehavior *floking[4];
};

