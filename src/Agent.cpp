#include "Agent.h"

using namespace std;

Agent::Agent() : sprite_texture(0),
position(Vector2D(100, 100)),
target(Vector2D(1000, 100)),
velocity(Vector2D(0, 0)),
mass(0.01),
speed(0.5),
max_force(5),
max_velocity(200),
orientation(0),
sprite_num_frames(0),
sprite_w(0),
sprite_h(0),
draw_sprite(false),
raycastLenght(150.f)

					
{
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);
}

void Agent::setBehavior(SteeringBehavior *behavior)
{
	steering_behaviour = behavior;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

float Agent::getMaxForce()
{
	return max_force;
}

float Agent::getMass()
{
	return mass;
}

float Agent::getOrientation()
{
	return orientation;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::update(float dtime, SDL_Event *event)
{

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}

	//Calcular intersecc
	//Cridar funcio SegmentSegment Interseccion. Si retorna true hi ha colisio i sha de cambiar el target rotant-lo per que no colisioni.



	// Apply the steering behavior
	steering_behaviour->applySteeringForce(this, dtime);
	
	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;

	Vector2D vel = velocity;
	raycastPos = position;
	//raycastPos += vel.Normalize() + raycastLenght;
	raycastPos.x += raycastLenght * cos(orientation * DEG2RAD);
	raycastPos.y += raycastLenght * sin(orientation * DEG2RAD);
	//(int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
}

void Agent::draw()
{
	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1*velocity.Length() + 250)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)raycastPos.x, (int)raycastPos.y);
	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));

	}
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}

void Agent::setAgentsPosition(std::vector<Vector2D> v)
{
	agentsPositions = v;
}

void Agent::setAgentsvelocities(std::vector<Vector2D> v)
{
	agentsVelocities = v;
}


