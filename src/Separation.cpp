#include "Separation.h"

Separation::Separation() : maxDistance(115.f) //100
{
}

Separation::~Separation()
{
}

Vector2D Separation::calculateSteeringForce(Agent* agent, float dtime)
{
	std::vector<Vector2D> positions = agent->getAgentsPosition();
	////////REGULAR maxDistance per cambiar cuana actua la força/////////
	//float maxDistance = 100.f; //fer variable privada de la clase Separation i inicialitzar en el constructor
	float distancia = 0; //modul positions de zombie i neighbour. Es compara amb maxDist el resultat, si distancia > 0 i ditancia < maxDist es calcula separationForce
	Vector2D v_agent_neighbour = 0;
	Vector2D totalForce = 0;
	Vector2D v;
	int cont = 0;

	for (int i = 0; i < positions.size(); i++)
	{

		//if (positions[i].x != agent->getPosition().x && positions[i].y != agent->getPosition().y) //comprovació de que no sigui el mateix
		//{
			
			distancia = v.Distance(agent->getPosition(), positions[i]); //Funciona amb aquest v?

			if (distancia > 0 && distancia < maxDistance)
			{
				v_agent_neighbour = agent->getPosition() - positions[i];
				v_agent_neighbour.Normalize();

				if (distancia <= 25.f)//30
				{
					
					//v_agent_neighbour /= (distancia / 20.f); // /5.f
					v_agent_neighbour /= (distancia / 17.f); // /5.f
				}
				else if (distancia <= 40.f)
				{
					
					v_agent_neighbour /= (distancia / 10.5f);
				}
				else if (distancia <= 90)
				{
					v_agent_neighbour /= (distancia / 5.f);
				}
				else
				{
					v_agent_neighbour /= (distancia); // /5.f
				}

				totalForce += v_agent_neighbour;
				cont++;
			}
		//}
	}

	if (cont > 0)
	{
		totalForce /= (float)cont;
	}

	if (totalForce.Length() > 0) //Vect2D.lenght ens dona la magnitud del vector. 
	{
		totalForce.Normalize();
		totalForce *= agent->getMaxVelocity();
		Vector2D steeringForce = totalForce - agent->getVelocity();
		//steeringForce = steeringForce.Normalize();
		steeringForce.Normalize();
		return steeringForce * agent->getMaxForce();
	}

	return Vector2D(0);
}
