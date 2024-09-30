#include "WeightedBlending.h"

WeightedBlending::WeightedBlending()
{

	floking[0] = new Cohesion();
	floking[1] = new Alignment();
	floking[2] = new Separation();
	floking[3] = new Seek();

}

WeightedBlending::~WeightedBlending()
{
}

Vector2D WeightedBlending::calculateSteeringForce(Agent* agent, float dtime)
{
	//Tota la llogica: cridar a calculate floking[x].calculateSteeringForce() i anar guardant-ho en Vectors2D. Aplicar les K a cada força retornar una F resultant
	Vector2D choesionForce, alignmentForce, SeparationForce, SeekForce;

	//Implementar en .h les consts *k* i inicalitzarles en el constructor. Es pot utilitzar GUI per jugar amb les consts mentres probem?

	choesionForce = floking[0]->calculateSteeringForce(agent, dtime);
	alignmentForce = floking[1]->calculateSteeringForce(agent, dtime);
	SeparationForce = floking[2]->calculateSteeringForce(agent, dtime);
	SeekForce = floking[3]->calculateSteeringForce(agent, dtime);

	return choesionForce*0.315 + SeparationForce*0.79 + alignmentForce*0.3 + SeekForce*0.315; //+ alignmentForce + SeparationForce;
	//return choesionForce*0.3 + SeparationForce*0.69 + SeekForce*0.35; //+ alignmentForce + SeparationForce;
	//return choesionForce*0.3 + SeparationForce*0.8 + SeekForce*0.4; //Separation maxDistance 100.f
}
