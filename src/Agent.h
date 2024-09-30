#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"
#include <vector>

class Agent
{
public:
	class SteeringBehavior //podria estar fora
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual Vector2D calculateSteeringForce(Agent* agent, float dtime) = 0;
		void applySteeringForce(Agent *agent, float dtime) {
			Vector2D steeringForce = this->calculateSteeringForce(agent, dtime);
			Vector2D acceleration = steeringForce / agent->getMass();
			Vector2D velocity = agent->getVelocity() + acceleration * dtime;
			velocity.Normalize();
			velocity *= agent->getMaxVelocity();
			agent->setVelocity(velocity);
			agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
		};
	};
private:
	/// 
	float raycastLenght;
	Vector2D raycastPos;
	///
	Vector2D centerPosition;
	///

	///
	
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	std::vector<Vector2D> agentsPositions;
	std::vector<Vector2D> agentsVelocities;

	float mass;
	float speed;
	float orientation;
	float max_force;
	float max_velocity;

	bool isOnCollision = false;
	bool collisionStarted = false;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	inline Vector2D getRaycastPosition() const { return raycastPos; };
	Vector2D getTarget();
	inline Vector2D getCenterPosition()  const{ return centerPosition; };
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	float getOrientation();
	inline void setCenterPosition(Vector2D temp) { centerPosition = temp; };
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	void setAgentsPosition(std::vector<Vector2D> v);
	void setAgentsvelocities(std::vector<Vector2D> v);
	inline void setIsOnCollision(bool b) { isOnCollision = b; }
	inline void setCollisionStarted(bool b) { collisionStarted = b; }
	inline std::vector<Vector2D> getAgentsPosition() const { return agentsPositions; }
	inline bool getIsOnCollision() const { return isOnCollision; }
	inline bool getCollisionStarted() const { return collisionStarted; }
	inline std::vector<Vector2D> getAgentsVelocities() const { return agentsVelocities; }
	
};
