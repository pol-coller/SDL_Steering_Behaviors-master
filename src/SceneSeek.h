#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Obstacle.h"

class SceneSeek :
	public Scene
{
public:
	SceneSeek();
	~SceneSeek();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();
private:
	bool oneTry = false;
	bool isOnColision = false;
	bool colisionStarted = false;
	std::vector<Agent*> agents;
	Obstacle* tempObstacle;
	Vector2D target;
	Vector2D vectorAvoidance;
	int avoidDistance = 3;
};