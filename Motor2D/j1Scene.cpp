#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Colliders.h"
#include "j1Scene.h"
#include "j1EntityManager.h"
#include "Player.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;
	Map_1 = true;
	Map_2 = false;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	win_height = App->win->screen_surface->h;
	win_width = App->win->screen_surface->w;
	App->map->Load("Test2.tmx");
	App->map->Draw_Colliders();
	App->map->LoadEntities();
	map_height = App->map->data.height * App->map->data.tile_height;
	map_width = App->map->data.width * App->map->data.tile_width;
	App->entities->AddEntity(PROP, 0, 0);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate_Scene1 ", Profiler::Color::Orchid)
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	BROFILER_CATEGORY("Update_Scene1 ", Profiler::Color::MediumOrchid)

 	win_position_y = App->render->camera.y*-1;


	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		if (App->Cap_on)
		{
			App->Cap_on = false;
		}
		else
		{
			App->Cap_on = true;
		}
	}	
		App->render->camera.x = -(App->entities->player->position.x + App->entities->player->move.frames[0].w / 2) + App->render->camera.w / 2;
		App->render->camera.y = -(App->entities->player->position.y + App->entities->player->move.frames[0].h / 2) + App->render->camera.h / 2;

	

	int order = 0;

	if (App->entities->player->position.y > 200)
	{
		order = 1;
	}
	else
	{
		order = 3;
	}

	App->map->Draw();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PosUpdate_Scene1 ", Profiler::Color::DarkOrchid)
	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		exit = false;

	return exit;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	App->entities->CleanUp();
	App->colliders->CleanUp();
	App->map->CleanUp();

	return true;
}