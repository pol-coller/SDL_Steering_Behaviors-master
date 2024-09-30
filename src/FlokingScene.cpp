#include "FlokingScene.h"
#include "Seek.h"
#include "Flee.h"
#include "Wander.h"
#include "Flocking.h"


FlokingScene::FlokingScene()
{
	Agent* agent = new Agent;
	int pos_x = 520, pos_y = 150;

	//cambiar per instanciar mes agents
	for (int i = 0; i < 10; i++)
	{
		agent = new Agent();

		agent->setBehavior(new Flocking);

		agent->setPosition(Vector2D(pos_x, pos_y));
		agent->setTarget(Vector2D(640, 360));  //¿?¿?¿¿
		agent->loadSpriteTexture("../res/soldier.png", 4);
		agents.push_back(agent);
		target = Vector2D(640, 360);

		pos_x += 20;
		pos_y += 10;
	}

}

FlokingScene::~FlokingScene()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void FlokingScene::update(float dtime, SDL_Event* event)
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
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}

}

void FlokingScene::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* FlokingScene::getTitle()
{
	return "SDL Steering Behaviors :: Floking Demo";
}