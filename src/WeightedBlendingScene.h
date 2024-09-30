#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "WeightedBlending.h"
#include "Wander.h"
class WeightedBlendingScene :
	public Scene
{	
public:
	WeightedBlendingScene();
	~WeightedBlendingScene();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();
private:
	bool oneTry = false;
	bool isOnColision = false;
	bool colisionStarted = false;
	std::vector<Agent*> zombies;

	Obstacle* tempObstacle;
	Agent* soldier;

	Vector2D vectorAvoidance;
	int avoidDistance = 3;
};

