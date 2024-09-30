#pragma once
//#include "SceneWander.h"
#include <vector>
#include "Scene.h"
#include "Agent.h"


class FlokingScene : 
	public Scene
{
	public:
		FlokingScene();
		~FlokingScene();
		void update(float dtime, SDL_Event* event);
		void draw();
		const char* getTitle();
	private:
		std::vector<Agent*> agents;
		Vector2D target;
};

