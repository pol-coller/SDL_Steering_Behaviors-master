#include "SceneWander.h"
#include "Wander.h"

SceneWander::SceneWander()
{
	Agent* agent = new Agent;
	agent->setBehavior(new Wander);
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

SceneWander::~SceneWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneWander::update(float dtime, SDL_Event* event)
{
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			//target = Vector2D((float)(event->button.x), (float)(event->button.y));
			//agents[0]->setTarget(target);  //Utilitzat per fer els calculs
		}
		break;
	default:
		break;
	}
	agents[0]->update(dtime, event);
}

void SceneWander::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}