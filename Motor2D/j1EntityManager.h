#ifndef __J1ENEMIES_H__
#define __J1ENEMIES_H__
#include "j1Module.h"

#define MAX_PROPS 100
#define SCREEN_SIZE 1
class Entity;
class Player;
struct SDL_Texture;
enum entitytype{
	NO_TYPE,PLAYER,PROP,COIN
};

struct EnemyInfo
{
	entitytype type = entitytype::NO_TYPE;
	int x, y;
};

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	bool AddEntity(entitytype type, int x, int y, int wave = 1, int id = 0);

private:

	void CreateEntity(const EnemyInfo& info);

public:

	Entity*				entities[MAX_PROPS];
	Player*				player = nullptr;
	pugi::xml_node		entity_config;
	pugi::xml_document	config_file;
	SDL_Texture*		sprites_prop = nullptr;
	SDL_Texture*		sprites_player = nullptr;
	bool				draw_underlayed = false;
	bool				Slowmo = false;
	uint				SlowAnimationCap = 1;
	uint				order = 0;
	float				height = 0;
	float				Slowmo_dt = 0;

private:
	
	EnemyInfo			queue[MAX_PROPS];

};

#endif // __J1ENEMIES_H__