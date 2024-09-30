#include "Obstacle.h"
#include "Agent.h"
//Obstacle::Obstacle(Vector2D i, Vector2D f) :initPos(i), finalPos(f){}
Obstacle::Obstacle()
{

}
void Obstacle::Draw()
{
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 200, 100, 200, 400);
}



