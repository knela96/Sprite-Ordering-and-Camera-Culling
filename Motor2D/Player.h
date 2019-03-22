#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "j1EntityManager.h"
#include "Entity.h"

class Player : public Entity
{

public:

	Player(int x, int y, entitytype type);
	~Player();
	bool Awake(pugi::xml_node&);
	bool Start();
	bool Update(float dt);
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
public:

	SDL_Texture*	graphics = nullptr;
	Animation*		current_animation = nullptr;
	Animation		move;
	Collider*		collider_player=nullptr;
	uint			win_width;
	uint			win_height;
	uint			win_scale;
	float			velocity;

};

#endif // _PLAYER_H_
