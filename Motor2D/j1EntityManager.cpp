#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Colliders.h"
#include "j1EntityManager.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "Entity.h"
#include "Player.h"
#include "Prop.h"

#define SPAWN_MARGIN 2000

j1EntityManager::j1EntityManager()
{
	name.create("entity");
	
	for (uint i = 0; i < MAX_PROPS; ++i)
	{
		entities[i] = nullptr;
	}
}

// Destructor
j1EntityManager::~j1EntityManager()
{
}

bool j1EntityManager::Awake(pugi::xml_node& config)
{
	config_file.load_file("config.xml");
	entity_config = config_file.child("config").child("entity");

	return true;
}

bool j1EntityManager::Start()
{
	LOG("loading enemies");

	sprites_player = App->tex->Load("assets/square.png");
	sprites_prop = App->tex->Load("assets/prop.png");


	if (player == nullptr)
	{
		player = new Player(10, 100, PLAYER);
		player->Awake(entity_config);
		player->Start();
	}
	else
	{
		player->Start();
	}

	return true;
}

bool j1EntityManager::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdate Entities", Profiler::Color::Orange);
	
	for (uint i = 0; i < MAX_PROPS; ++i)
	{
		if (queue[i].type != entitytype::NO_TYPE)
		{
			if (-queue[i].y < App->render->camera.y + SPAWN_MARGIN)
			{
				CreateEntity(queue[i]);
				queue[i].type = entitytype::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].y * SCREEN_SIZE);
			}
		}
	}

	return true;
}

// Called before render is available
bool j1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("Update Entities", Profiler::Color::OrangeRed);

	if (App->scene->active)
	{
		if (Slowmo)
		{
			Slowmo_dt = dt / 4;
		}
		else
		{
			Slowmo_dt = dt;
		}

		for (uint i = 0; i < MAX_PROPS; ++i)
		{
			if (entities[i] != nullptr)
			{
				entities[i]->Update(Slowmo_dt);
			}
		}

		if (player != nullptr)
		{
			player->Update(dt);
			player->Draw(sprites_player, player->scale, dt);
		}

		for (uint i = 0; i < MAX_PROPS; ++i)
		{
			if (entities[i] != nullptr && (entities[i]->collider != nullptr))
			{
				if (entities[i]->GetType() == PROP)
				{
					entities[i]->Draw(sprites_prop, entities[i]->scale, Slowmo_dt);
				}
			}
		}

		for (uint i = 0; i < MAX_PROPS; ++i)
		{
			if (entities[i] != nullptr && entities[i]->die)
			{
				entities[i]->position.x = -2000;
				entities[i]->position.y = 0;
				entities[i]->original_pos.x = -2000;
				entities[i]->original_pos.y = 0;
				entities[i]->die = false;
				entities[i]->alive = true;
			}
		}

		for (uint i = 0; i < MAX_PROPS; ++i)
		{
			if (entities[i] != nullptr && (entities[i]->collider == nullptr))
			{
				if (entities[i]->GetType() == PROP)
				{
					entities[i]->Draw(sprites_prop, entities[i]->scale, Slowmo_dt);
				}
			}
		}
	}
	return true;
}

bool j1EntityManager::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdate Entities", Profiler::Color::DarkOrange);
	
	return true;
}

bool j1EntityManager::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_PROPS; ++i)
	{
		if (entities[i] != nullptr)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
		if (queue[i].type != NO_TYPE)
		{
			queue[i].type = NO_TYPE;
		}
	}
	
	App->tex->UnLoad(sprites_prop);
	App->tex->UnLoad(sprites_player);

	return true;
}

bool j1EntityManager::AddEntity(entitytype type, int x, int y, int wave, int id)
{
	bool ret = false;

	for (uint i = 0; i < MAX_PROPS; ++i)
	{
		if (queue[i].type == entitytype::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void j1EntityManager::CreateEntity(const EnemyInfo& info)
{
	uint i = 0;
	for (; entities[i] != nullptr && i < MAX_PROPS; ++i);

	if (i != MAX_PROPS)
	{
		switch (info.type)
		{
		case entitytype::PLAYER:
			entities[i] = new Player(info.x, info.y, info.type);
			break;
		case entitytype::PROP:
			entities[i] = new Prop(info.x, info.y, info.type);
			break;
		}
	}
}

bool j1EntityManager::Load(pugi::xml_node& data)
{

	if (player != nullptr)
	{
		player->Load(data);
	}

	
	return true;
}

bool j1EntityManager::Save(pugi::xml_node& data) const
{
	if (player != nullptr)
	{
		player->Save(data);
	}

	return true;
}