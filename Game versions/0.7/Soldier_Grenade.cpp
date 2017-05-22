#include "Application.h"
#include "Soldier_Grenade.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleParticles.h"
#include "ModuleScene1.h"
#include <stdlib.h>
#include "ModuleEnemies.h"
#include <time.h>

#include "SDL/include/SDL_timer.h"

Enemy_SoldierGrenade::Enemy_SoldierGrenade(int x, int y) : Enemy(x, y)
{
	//ANIMATION TURN1 (SOLDIER WHO THROWS GRENADES)
	turn1.PushBack({ 56, 110, 16, 22 }); //normal

	//ANIMATION TURN2 (SOLDIER WHO THROWS GRENADES)
	turn2.PushBack({ 74, 110, 16, 22 }); //down
	turn2.PushBack({ 91, 110, 16, 22 }); //MORE down

	turn1.speed = 0.1f;
	turn2.speed = 0.05f;

	die.PushBack({ 6, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });
	die.PushBack({ 25, 111, 16, 27 });
	die.PushBack({ 40, 104, 15, 27 });

	animation = &turn1;

	collider = App->collision->AddCollider({ 0, 0, 18, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_SoldierGrenade::Move()
{
	currentTime = SDL_GetTicks();
	currentTime -= lastTime;

	//Animation
	cont++;
	if (cont == 130) {
		animation = &turn2;
	}

	if (cont == 230) {
		animation = &turn1;
		cont = 0;
	}
	//

	//SHOT
	rand1 = rand() % 500;
	num_shots = rand() % 4;

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
			App->particlesenemies->AddParticle(App->particlesenemies->grenade, position.x, (position.y + 25), COLLIDER_PLAYER_GRENADE, NULL, enemyplayeru); //position.y+30+space
			space = rand() % 10 + 5;
		}

		//App->particlesenemies->bala.position.x = (position.x + App->particlesenemies->bala.speed.x);
		//App->particlesenemies->bala.position.y = ((position.y + 25) + App->particlesenemies->bala.speed.y);

		space = 0;
	}

	if (dieB == false)
		lastTime = SDL_GetTicks();


	if (dieB == true) {

		animation = &die;
		die.speed = 0.1f;
		if (currentTime > 800)
			Esperanza = false;

	}

	checking++;
	one = rand() % 100;
}

void Enemy_SoldierGrenade::OnCollision(Collider* c1, Collider* c2) {
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