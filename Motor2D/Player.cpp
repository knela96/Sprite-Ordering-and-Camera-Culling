#include "Player.h"
#include "j1Window.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "j1Textures.h"
#include "j1Colliders.h"
#include "p2Point.h"
#include "j1Render.h"
#include "j1Map.h"
#include "j1Scene.h"


Player::Player(int x, int y, entitytype type) : Entity(x, y,type)
{
	LOG("Loading Player Sheet");

	//movement animation
	{
		move.PushBack({ 0,0,50,120 });
		move.loop = true;
		move.speed = 30.0f;
	}

	//Init Screen vars
	win_width = App->win->screen_surface->w;
	win_height = App->win->screen_surface->h;
	win_scale = App->win->GetScale();
	animation = &move;
	scale = 0.2f;
	initial_pos.x = original_pos.x;
}

bool Player::Awake(pugi::xml_node& entity_config){
	pugi::xml_node player = entity_config.child("player");
	original_pos.x = player.child("position").attribute("pos_x").as_float(10);
	original_pos.y = player.child("position").attribute("pos_y").as_float(10);
	velocity = player.child("velocity").attribute("value").as_float(1);
	bool ret = true;
	return ret;
}


Player::~Player(){
	if (collider_player != nullptr)
		collider_player->to_delete = true;
}

bool Player::Start(){
	collider = App->colliders->AddCollider({ (int)original_pos.x, (int)original_pos.y, (int)(50*scale), (int)(80*scale) }, COLLIDER_PLAYER, (j1Module*)App->entities);
	win_width = App->win->screen_surface->w;
	win_height = App->win->screen_surface->h;
	win_scale = App->win->GetScale();
	order = 0;
	height = 0.0f;
	
	return true;
}

bool Player::Update(float dt)
{
	SDL_Event e;

	//MOVE_LEFT
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT){
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE){
			if (original_pos.x >= -1000){
				speed.x = -(velocity)*dt;
				original_pos.x += speed.x;
			}

		}
	}
		//MOVE_RIGHT
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT){
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE){
				if (original_pos.x < 25600){
					speed.x = (velocity)*dt;
					original_pos.x += speed.x;
				}

			}
		}
			//MOVE_DOWN
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT){
				if (original_pos.x >= -1000){
					speed.y = velocity * dt;
					original_pos.y += speed.y;
				}
			}

			//MOVE_UP
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT){
				if (original_pos.x >= 0){
					speed.y = -(velocity)*dt;
					original_pos.y += speed.y;
				}
			}

			position = original_pos;

			iPoint pos1 = App->map->WorldToMap((int)position.x, (int)position.y); LOG("%i - %i", pos1.x, pos1.y);
			return true;
}

bool Player::Load(pugi::xml_node& data){
	int map = data.child("player").attribute("Map").as_int();
	int x = data.child("player").attribute("x").as_int();
	int y = data.child("player").attribute("y").as_int();
	return true;
}


bool Player::Save(pugi::xml_node& data) const{
	pugi::xml_node playernode = data.append_child("player");

	playernode.append_attribute("x") = original_pos.x;
	playernode.append_attribute("y") = original_pos.y;

	return true;
}