#pragma once
#include "Vector2D.h"
class Obstacle
{
public:
	Obstacle(Vector2D i, Vector2D l);
	Obstacle();
	~Obstacle();
	void Draw();
	inline Vector2D getInitPos() const { return initPos; }
	inline Vector2D getFinalPos() const { return finalPos; }
private:
	Vector2D initPos;
	Vector2D finalPos;
};

