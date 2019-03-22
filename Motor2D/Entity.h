#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j1EntityManager.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "p2animation.h"
#include "p2Log.h"
#include "SDL/include/SDL_timer.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include "p2Path.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

struct SDL_Texture;
struct Collider;

class Entity:public j1EntityManager
{
public:

	Entity(int x, int y,entitytype type);
	virtual ~Entity();

	const Collider*		GetCollider() const;
	const entitytype	GetType()const;
	bool				Awake(pugi::xml_node&);
	void				Draw(SDL_Texture* sprites, float direction,float dt);
	virtual bool		Update(float dt)=0;

public:
	
	entitytype	type;
	fPoint			position = { 0.0f,0.0f };
	fPoint			original_pos = { 0.0f,0.0f };
	fPoint			speed = { 0.0f,0.0f }; 
	fPoint			initial_pos = { 0.0f,0.0f };
	float			scale = 0;
	bool			left = false;
	bool			right = true;
	bool			alive = true;
	bool			die = false;
	bool			going = false;
	Collider*		collider = nullptr;

protected:

	Animation*		animation = nullptr;
};

#endif // __ENEMY_H__