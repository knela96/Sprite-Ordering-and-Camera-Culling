#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 1000

#include "j1Module.h"
#include "Quadtree.h"

#include <list>

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
};

struct Collider
{
	SDL_Rect		rect;
	bool			to_delete = false;
	COLLIDER_TYPE	type;
	j1Module*		callback = nullptr;

	
	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :rect(rectangle),type(type),	callback(callback){}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}
};

class j1Colliders : public j1Module
{
public:

	j1Colliders();
	~j1Colliders();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();
	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();
	int numberCollisions_1;
	int numberCollisions_2;

private:

	Collider*		colliders[MAX_COLLIDERS];
	bool			debug = false;
	float			distance = 0;
	float			Slowdt;
	list<Collider*>	ListToCollide;
	Quadtree*		ColQuadtree;
};

#endif // __ModuleCollision_H__