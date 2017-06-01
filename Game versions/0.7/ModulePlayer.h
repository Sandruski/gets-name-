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
	void OnCollisionRev(Collider* c1, Collider* c2);
	void OnCollisionSecretRooms(Collider* c1, Collider* c2);
	void Shot();

	bool detectionitem[10];

	update_status Update();
	bool CleanUp();

	SDL_Texture* graphics = nullptr;
	SDL_Texture* bullets = nullptr;
	Animation idleF;
	Animation forward, right, backward, left, diagWD, diagWA, diagSD, diagSA, invisible, grenade, die, waterDie, stairsRoom;
	iPoint position;
	Animation* current_animation = &idleF;
	Collider* coll;
	Collider* collrev;
	Collider* feetC;
	Collider* grenadeC;
	Collider* follow_p;
	Collider* follow_p1;
	Collider* follow_p2;
	Collider* follow_p3;

	SDL_Rect r, R;
	int vides = 3;
	bool move = true;
	bool move2 = true;
	bool waterB = true;
	bool enemyB = true;
	bool GOD = false;
	int speed;
	bool timeW = false;
	bool collW = false;
	bool collA = false;
	bool collS = false;
	bool collD = false;
	bool stairsDown = true;
	bool stairsUp = true;
	bool granade = false;
	bool granadeUp = false;
	bool GunPowerUp = false;
	int SoldierPowerUp = 0;

	bool cooldown = false;
	uint lastTime, currentTime, allTime, finalTime;

	bool non_grenade = false;
	bool play_ending = false;
	iPoint p1, p2, p3, p4;
	int check_grenade = 1, check_nonshoot = 1, update_position_grenade = 0;

	int count = 0;
	int randomsound;
	//Save position where player died
	int save_player_position = 0;
	int revTime = 0;
	SDL_Rect help;
	SDL_Rect  hpRev1, hpRev2, hpRev3, hpRev4;
	SDL_Rect dead2player;
	
	bool contdead = 0;
	bool detectionlive = 0;
	
};

#endif