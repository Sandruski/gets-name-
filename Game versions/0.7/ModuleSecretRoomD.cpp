#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSecretRoom1A.h"
#include "ModuleSecretRoomB.h"
#include "ModuleSecretRoomC.h"
#include "ModuleSecretRoomD.h"
#include "ModuleSecretRoomE.h"
#include "ModuleMenu.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleEND.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleEnding.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleParticlesGrenade.h"
#include "ModuleParticlesGrenade1.h"
#include "ModuleParticles.h"
#include "ModuleCinematic.h"
#include "ModuleScene1.h"
#include "ModuleUI.h"
#include <windows.h>

ModuleSecretRoomD::ModuleSecretRoomD() {

}
ModuleSecretRoomD::~ModuleSecretRoomD() {

}

bool ModuleSecretRoomD::Start() {
	RoomD = App->textures->Load("Assets/Background/Secret_Rooms/1-1/salasecretea1-D.png");
	background.x = 0;
	background.y = 0;
	background.w = 256;
	background.h = 447;

	App->collision->Enable();
	App->particles->Enable();
	App->particlesenemies->Enable();
	App->particlesgrenade->Enable();
	App->particlesgrenade1->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->UI->Enable();

	App->player->current_animation = &App->player->forward;

	check_player = 0;

	//Camera and player parametres
	App->player->position.x = SCREEN_WIDTH / 2;
	App->player->position.y = 410;
	App->scene_1->current_start_pos = SCREEN_HEIGHT;
	App->render->camera.y = -3 * SCREEN_HEIGHT;
	App->scene_1->cont = 0;

	//COLLIDERS
	App->collision->AddCollider({ 0,0, 15, 448 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 16,266, 32, 54 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 16,120, 32, 54 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 16,8, 96, 70 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 109,8, 35, 23 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 96, 120, 64, 52 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 144,8, 96, 70 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 208,120, 33, 54 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 208, 216, 33, 40 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 208,97, 32, 55 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 208,298, 32, 55 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 240,0, 16, 448 }, COLLIDER_WALL, this);
	App->collision->AddCollider({ 16, 442, 224, 6 }, COLLIDER_WALL, this);




	//ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 20, 247);
	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 21, 232);

	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 214, 283);

	App->enemies->AddEnemy(ENEMY_TYPES::SOLDIER, 213, 193);

	return true;
}
update_status ModuleSecretRoomD::Update() {
	App->render->Blit(RoomD, w, h, &background);

	//Move camera UP
	if (App->player->position.y <= 220 && App->render->camera.y < 0) {
		check_player++;

		if (check_player % 2 == 0) {
			App->player->position.y--;
		}

		App->player->move = false;
		App->scene_1->cont += 2;
		App->player->current_animation = &App->player->forward;
		App->player->forward.Start();
		App->render->camera.y += 6;
	}
	else {
		App->player->forward.Stop();
		App->player->move = true;
	}
	//

	//Move camera DOWN
	if (App->player->position.y > 220 && App->render->camera.y > -3 * SCREEN_HEIGHT) {
		check_player++;

		if (check_player % 2 == 0) {
			App->player->position.y++;
		}

		App->player->move = false;
		App->scene_1->cont -= 2;
		App->player->current_animation = &App->player->backward;
		App->player->backward.Start();
		App->render->camera.y -= 6;
	}
	else {
		App->player->backward.Stop();
	}
	//

	if (App->input->keyboard[SDL_SCANCODE_1] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->room1A, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_2] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomB, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_3] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomC, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_4] == 1 && KEY_DOWN) {
		App->render->UP = false;

		App->scene_1->start = false;
		App->scene_1->start1 = false;
		App->scene_1->start2 = false;
		App->scene_1->start3 = false;
		App->scene_1->start4 = true;
		App->scene_1->start5 = false;

		App->fade->FadeToBlack(this, App->scene_1, 1);

	}
	if (App->input->keyboard[SDL_SCANCODE_5] == 1 && KEY_DOWN) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->roomE, 1);
	}

	return UPDATE_CONTINUE;
}
bool ModuleSecretRoomD::CleanUp() {
	App->textures->Unload(RoomD);

	App->UI->Disable();
	App->enemies->Disable();
	App->player->Disable();
	App->particlesgrenade1->Disable();
	App->particlesgrenade->Disable();
	App->particlesenemies->Disable();
	App->particles->Disable();
	App->collision->Disable();

	return true;
}