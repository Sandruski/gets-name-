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
	void OnCollisionWall(Collider* c1, Collider* c2);
	void OnCollisionItem(Collider* c1, Collider* c2);
	void OnCollisionWater(Collider* c1, Collider* c2);
	void OnCollisionEnemy(Collider* c1, Collider* c2);


	bool detectionitem[9];

	update_status Update();
	bool CleanUp();

	SDL_Texture* graphics = nullptr;
	SDL_Texture* bullets = nullptr;
	Animation idleF;
	Animation forward, right, backward, left, diagWD, diagWA, diagSD, diagSA, invisible, grenade, die, waterDie;
	iPoint position;
	Animation* current_animation = &idleF;
	Collider* coll;
	Collider* feetC;
	SDL_Rect r;
	int vides = 3;
	bool move = true;
	bool waterB = true;
	bool enemyB = true;
	bool GOD = false;
	int speed;
	bool timeW = false;
	uint lastTime, currentTime;

	iPoint x1, x2, x3, x4;
	int check_grenade = 1, check_nonshoot = 1, update_position_grenade = 0;
};

#endif