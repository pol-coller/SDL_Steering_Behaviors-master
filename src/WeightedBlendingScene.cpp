#include "WeightedBlendingScene.h"
WeightedBlendingScene::WeightedBlendingScene()
{
	Agent* agent = new Agent;
	int pos_x = 520, pos_y = 150;

	//cambiar per instanciar mes agents
	soldier = new Agent();
	soldier->setBehavior(new Wander);
	//soldier->setBehavior(new WeightedBlending);
	soldier->setPosition(Vector2D(10,10));
	soldier->loadSpriteTexture("../res/soldier.png", 4);


	tempObstacle = new Obstacle;
	for (int i = 0; i < 8; i++)
	{
		agent = new Agent();

		agent->setBehavior(new WeightedBlending);

		agent->setPosition(Vector2D(pos_x, pos_y));
		agent->setTarget(soldier->getPosition());
		agent->loadSpriteTexture("../res/zombie1.png", 8);
		zombies.push_back(agent);

		pos_y += 200;
		pos_x += 280;
	}
}
WeightedBlendingScene::~WeightedBlendingScene()
{
	for (int i = 0; i < (int)zombies.size(); i++)
	{
		delete zombies[i];
	}
	delete soldier;
}

void WeightedBlendingScene::update(float dtime, SDL_Event* event)
{
	switch (event->type) 
	{
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			oneTry = true;
		}
		break;
	default:
		break;
	}

	Vector2D a, b;
	a.x = 400; a.y = 100;
	b.x = 400; b.y = 400;

	Vector2D tempCenterPos=Vector2D(0,0);

	tempCenterPos /= zombies.size();

	std::vector<Vector2D> v_pos;
	std::vector<Vector2D> v_vels;

	//Update positions, vels zombies, pos del centre de la horda i del target poder fer el Separation-Choesion i Seek
	for (int i = 0; i < (int)zombies.size(); i++)
	{
		zombies[i]->setCenterPosition(tempCenterPos);  
		zombies[i]->setTarget(soldier->getPosition());
		v_pos.push_back(zombies[i]->getPosition());
		v_vels.push_back(zombies[i]->getVelocity());
	}

	//Pasem vector de posicions i vels a cada zombie
	for (int i = 0; i < (int)zombies.size(); i++)
	{
		zombies[i]->setAgentsPosition(v_pos);
		zombies[i]->setAgentsvelocities(v_vels);
	}

	for (int i = 0; i < zombies.size(); i++)
	{
		if (oneTry)
		{
			isOnColision = Vector2DUtils::SegmentSegmentIntersection(zombies[i]->getPosition(), zombies[i]->getRaycastPosition(),
				a, b);
			zombies[i]->setIsOnCollision(isOnColision);
		}
	}
	for (int i = 0; i < (int)zombies.size(); i++)
	{
		tempCenterPos += zombies[i]->getPosition();
	}
	for (int i = 0; i < zombies.size(); i++)
	{
		if (zombies[i]->getCollisionStarted()) {

			if (soldier->getPosition().y < 250) {
				vectorAvoidance = Vector2D(soldier->getPosition().x, soldier->getPosition().y * -avoidDistance);
				//vectorAvoidance = target * -avoidDistance;
				zombies[i]->setTarget(vectorAvoidance);
			}
			else {
				//vectorAvoidance = Vector2D(target.x, target.y * avoidDistance);
				if (soldier->getPosition().x < 400) {
					vectorAvoidance = soldier->getPosition() * avoidDistance;
				}
				else {
					vectorAvoidance = Vector2D(soldier->getPosition().x * -avoidDistance, soldier->getPosition().y * avoidDistance);
				}
				zombies[i]->setTarget(vectorAvoidance);
			}
		}
		else {
			zombies[i]->setTarget(soldier->getPosition());
		}
		if (zombies[i]->getPosition().y >= 450) {
			colisionStarted = false;
		}
		if (zombies[i]->getPosition().y <= 50) {
			colisionStarted = false;
		}
	}
	//Updates de zombies i soldier
	for (int i = 0; i < (int)zombies.size(); i++)
	{
		zombies[i]->update(dtime, event);
	}
	soldier->update(dtime, event);
}

void WeightedBlendingScene::draw()
{
	for (int i = 0; i < (int)zombies.size(); i++)
	{
		zombies[i]->draw();
	}
	soldier->draw();

	tempObstacle->Draw();
}
const char* WeightedBlendingScene::getTitle()
{
	return "SDL Steering Behaviors :: WeightedBlending Floking Demo";
}

