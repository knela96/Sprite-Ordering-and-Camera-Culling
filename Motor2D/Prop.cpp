#include "Prop.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1EntityManager.h"
#include "Player.h"
#include "j1Colliders.h"

Prop::Prop(int x, int y, entitytype type):Entity(x, y, type){
	scale = 1.0f;
	order = 3;
	App->tex->GetSize(App->entities->sprites_prop, height, width);
	collider = App->colliders->AddCollider({(int)position.x,(int)position.y,(int)(50 * scale), (int)(50 * scale) }, COLLIDER_WALL, (j1Module*)App->entities);
}

Prop::~Prop(){}

bool Prop::Update(float dt)
{
	//TODO 2: Create a method that compares adn determines if the prop has to be rendered before or after the player
	if (App->entities->player->position.y < position.y) { order = App->entities->player->order + 1;}
	else { order = App->entities->player->order - 1;}

	return true;
}
