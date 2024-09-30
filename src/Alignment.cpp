#include "Alignment.h"

Alignment::Alignment() : neighbourMaxDistance(200.f)
{
}

Alignment::~Alignment()
{
}

Vector2D Alignment::calculateSteeringForce(Agent* agent, float dtime)
{
	std::vector<Vector2D> velocities = agent->getAgentsVelocities();

	float distancia = 0; //modul positions de zombie i neighbour. Es compara amb maxDist el resultat, si distancia > 0 i ditancia < maxDist es calcula separationForce

	Vector2D sumVelocities = 0;
	Vector2D v;
	int cont = 0;

	for (int i = 0; i < velocities.size(); i++)
	{

		//if (positions[i].x != agent->getPosition().x && positions[i].y != agent->getPosition().y) //comprovació de que no sigui el mateix
		//{

		distancia = v.Distance(agent->getPosition(), velocities[i]); //Funciona amb aquest v?

		if (distancia > 0 && distancia < neighbourMaxDistance)
		{
			sumVelocities += velocities[i];
			cont++;
		}
		//}
	}

	if (cont > 0)
	{
		sumVelocities /= (float)cont;
		sumVelocities.Normalize();
		sumVelocities *= agent->getMaxVelocity();
		Vector2D steeringForce = sumVelocities - agent->getVelocity();
		steeringForce.Normalize();
		return steeringForce * agent->getMaxForce();
		
	}

	return Vector2D(0);
}
