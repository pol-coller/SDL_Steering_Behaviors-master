#include "Flocking.h"

Flocking::Flocking()
{
	evade = flee = seek = wander = true;
}
Flocking::~Flocking()
{

}
Vector2D Flocking::calculateAlignment(Agent* agent)
{
	return 0;
}
Vector2D Flocking::calculateCohesion(Agent* agent)
{
	return 0;
}
Vector2D Flocking::calculateSeparation(Agent* agent)
{
	return 0;
}
Vector2D Flocking::calculateSteeringForce(Agent* agent, float dtime)
{
	return 0;
}
