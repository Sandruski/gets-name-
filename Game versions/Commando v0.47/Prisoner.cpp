#include "Application.h"
#include "Prisoner.h"
#include "ModuleCollision.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"


Enemy_Prisoner::Enemy_Prisoner(int x, int y) : Enemy(x, y)
{
	//ANIMATION ANIMATED (PRISONER)
	animated.PushBack({ 61, 195, 15, 22 });
	animated.PushBack({ 79, 195, 15, 22 });
	animated.PushBack({ 96, 195, 15, 22 });

	//ANIMATION STAND (PRISONER)
	stand.PushBack({ 151, 195, 16, 22 });
	stand.PushBack({ 169, 195, 16, 22 });

	//ANIMATION RUN (PRISONER)
	run.PushBack({ 114, 195, 16, 32 });
	run.PushBack({ 133, 195, 16, 31 });

	animated.speed = 0.1f;
	stand.speed = 0.1f;
	run.speed = 0.1f;

	animation = &stand;

	collider = App->collision->AddCollider({ 0, 0, 18, 8 }, COLLIDER_TYPE::COLLIDER_PRISONER, (Module*)App->enemies);
}

void Enemy_Prisoner::Move()
{
	if (move == true)
	{
		animation = &run;
		position.x++;

	}
}


void Enemy_Prisoner::OnCollision(Collider* c1) {
	if (move == false)
		App->UI->score += 500;
	move = true;
}