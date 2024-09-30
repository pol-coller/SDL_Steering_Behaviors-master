#include "SceneSeek.h"
#include "Seek.h"
#include "Vector2D.h"

using namespace std;

SceneSeek::SceneSeek()
{
	Agent* agent = new Agent;
	agent->setBehavior(new Seek);
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	tempObstacle = new Obstacle;
}

SceneSeek::~SceneSeek()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneSeek::update(float dtime, SDL_Event* event)
{

	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:


		if (event->button.button == SDL_BUTTON_LEFT)
		{
			if (!colisionStarted) {
				target = Vector2D((float)(event->button.x), (float)(event->button.y));

				/*			 isOnColision = Vector2DUtils::SegmentSegmentIntersection(agents[0]->getPosition(), agents[0]->getRaycastPosition(),
								tempObstacle->getInitPos(), tempObstacle->getFinalPos());*/

				oneTry = true;
				//if (isOnColision)
				//{
				//	Vector2D v; v.x = 0; v.y = 0;
				//	agents[0]->setVelocity(v);
				//}
				//else

					//agents[0]->setTarget(target);  //Utilitzat per fer els calculs
			}
		}
		break;
	default:
		break;
	}

	Vector2D a, b;
	a.x = 400; a.y = 100;
	b.x = 400; b.y = 400;
	if (oneTry)
		isOnColision = Vector2DUtils::SegmentSegmentIntersection(agents[0]->getPosition(), agents[0]->getRaycastPosition(),
			a, b);

	if (isOnColision)
	{
		colisionStarted = true;
	}

	agents[0]->update(dtime, event);

	if (colisionStarted) {

		if (target.y < 250) {
			vectorAvoidance = Vector2D(target.x, target.y * -avoidDistance);
			//vectorAvoidance = target * -avoidDistance;
			agents[0]->setTarget(vectorAvoidance);
		}
		else {
			//vectorAvoidance = Vector2D(target.x, target.y * avoidDistance);
			if (target.x < 400) {
				vectorAvoidance = target * avoidDistance;
			}
			else {
				vectorAvoidance = Vector2D(target.x * -avoidDistance, target.y * avoidDistance);
			}
			agents[0]->setTarget(vectorAvoidance);
		}
	}
	else {
		agents[0]->setTarget(target);
	}
	if (agents[0]->getPosition().y >= 450) {
		colisionStarted = false;
	}
	if (agents[0]->getPosition().y <= 50) {
		colisionStarted = false;
	}
}

void SceneSeek::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	tempObstacle->Draw();
}

const char* SceneSeek::getTitle()
{
	return "SDL Steering Behaviors :: Seek Demo";
}