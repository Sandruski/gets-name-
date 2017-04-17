#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	void OnCollision(Collider* c1, Collider* c2);
	void OnCollisionWall();
	void OnCollisionItem(Collider* c1, Collider* c2);
	void OnCollisionWater(Collider* c1, Collider* c2);
	void OnCollisionEnemy(Collider* c1, Collider* c2);

	update_status Update();
	bool CleanUp();

	SDL_Texture* graphics = nullptr;
	SDL_Texture* bullets = nullptr;
	Animation idleF;
	Animation forward, right, backward, left, diagWD, diagWA, diagSD, diagSA, invisible;
	iPoint position;
	Animation* current_animation = &idleF;
	Collider* coll;
	Collider* feetC;
	bool destroyed = false;
	int speed;


};

#endif