#include "Application.h"
#include "Soldier_Rifle.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModuleParticlesGrenade1.h"
#include "ModulePlayer.h"
#include "ModuleScene1.h"
#include "ModuleParticlesEnemies.h"
#include <stdlib.h>
#include <time.h>
#include "ModuleEnemies.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

Enemy_SoldierRifle::Enemy_SoldierRifle(int x, int y) : Enemy(x, y)
{
	//ANIMATION TURN (SOLDIER WITH RIFLE)
	center.PushBack({ 107, 110, 18, 18 });
	left.PushBack({ 142, 110, 18, 18 });
	more_left.PushBack({ 159, 110, 18, 18 });
	right.PushBack({ 125, 110, 18, 18 });
	more_right.PushBack({ 177, 110, 18, 18 });

	center.speed = 0.1f;
	left.speed = 0.1f;
	more_left.speed = 0.1f;
	right.speed = 0.1f;
	more_right.speed = 0.1f;

	die.PushBack({ 6, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });
	die.PushBack({ 25, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });


	animation = &center;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierRifle::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	if (dieB == false) {
		lastTime = SDL_GetTicks();

		//MOVEMENT
		if (App->player->position.x <= position.x - 22) {
			animation = &more_left;
		}
		else if (App->player->position.x >= position.x + 22) {
			animation = &more_right;
		}
		else if (App->player->position.x > position.x - 22 && App->player->position.x < position.x - 2) {
			animation = &left;
		}
		else if (App->player->position.x < position.x + 22 && App->player->position.x > position.x + 2) {
			animation = &right;
		}
		else if (App->player->position.x >= position.x - 2 && App->player->position.x <= position.x + 2) {
			animation = &center;
		}

		//SHOT
		num_shots = rand() % 4;
		rand1 = rand() % 500;

		if (rand1 == 3 && App->player->position.y > position.y + 24) {

			enemyplayer.x = (App->player->position.x + 5) - position.x;
			enemyplayer.y = fabs(position.y + 25) - fabs(App->player->position.y + 10);

			module = sqrt((pow(enemyplayer.x, 2) + pow(enemyplayer.y, 2)));
			enemyplayeru.x = enemyplayer.x / module;
			enemyplayeru.y = enemyplayer.y / module;

			//angle = atan(enemyplayer.x / enemyplayer.y); do not use. Only if needed

			App->particlesenemies->bala.speed.x = enemyplayeru.x;
			App->particlesenemies->bala.speed.y = enemyplayeru.y;

			for (int i = 0; i <= num_shots; i++) {
				App->particlesenemies->AddParticle(App->particlesenemies->bala, position.x, (position.y + 25), COLLIDER_ENEMY_SHOT, NULL, enemyplayeru); //position.y+30+space
				space = rand() % 10 + 5;
			}

			//App->particlesenemies->bala.position.x = (position.x + App->particlesenemies->bala.speed.x);
			//App->particlesenemies->bala.position.y = ((position.y + 25) + App->particlesenemies->bala.speed.y);

			space = 0;
		}

		//Change of behaviour. Soldier walks backwards
		/*
		if (App->player->position.y <= position.y - 24) {

		}
		*/
	}

	if (dieB == true) {

		animation = &die;
		die.speed = 0.1f;
		if (currentTime > 800)
			Esperanza = false;
	}

	checking++;
	one = rand() % 100;
}

void Enemy_SoldierRifle::OnCollision(Collider* c1, Collider* c2) {
	if (c1->type == COLLIDER_ENEMY && c2->type == COLLIDER_END_OF_GRENADE) {
		App->scene_1->enemydiex = position.x;
		App->scene_1->enemydiey = position.y;

		if (checking % 2 == 0 || checking % 3 == 0 || checking % 5 == 0) {
			if (one % 2 == 0 || one % 3 == 0) {
				App->enemies->AddEnemy(ENEMY_TYPES::ITEM1, App->scene_1->enemydiex, App->scene_1->enemydiey);
			}
			else {
				App->enemies->AddEnemy(ENEMY_TYPES::ITEM2, App->scene_1->enemydiex, App->scene_1->enemydiey);
			}
		}
	}

	App->particles->AddParticle(App->particles->dieEnemie, c1->rect.x, c1->rect.y, COLLIDER_END_OF_GRENADE, NULL);	
}