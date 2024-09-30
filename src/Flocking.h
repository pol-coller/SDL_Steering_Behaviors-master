#pragma once
#include "Agent.h"

class Flocking:
	public Agent::SteeringBehavior
{
public:
	Flocking();
	~Flocking();
private:
	bool seek, flee, wander, arrive, pursue, evade;
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
	Vector2D calculateAlignment(Agent* agent);
	Vector2D calculateCohesion(Agent* agent);
	Vector2D calculateSeparation(Agent* agent);
};

