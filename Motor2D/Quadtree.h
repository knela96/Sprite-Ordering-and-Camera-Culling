#ifndef __QUADTREE_H__
#define __QUADTREE_H__ 

#define MAX_RAMIFICATIONS 10

#include "SDL/include/SDL_rect.h"
#include <vector>
#include <array>
#include <list>

class ImageRender;
struct Collider;

using namespace std;

class Quadtree
{
public:
	Quadtree(){
		Quadrant = { 0,0,0,0 };
		for (int i = 0; i < ramifications.size(); i++){ramifications[i] = nullptr;}
		ramification = 0;
	}

	Quadtree(SDL_Rect rect, int ramification){
		Quadrant = rect;
		for (int i = 0; i < ramifications.size(); i++){ramifications[i] = nullptr;}
		ramification = ramification;
	}

	~Quadtree(){Clear();}

	void Clear();
	void Split();
	void QuadDrawer();
	int getIndex(const SDL_Rect& r);
	bool insert(ImageRender* Object);
	bool IfInside(const SDL_Rect& r);
	vector<ImageRender*> PushCollisionVector(vector<ImageRender*> &ObjList, const SDL_Rect& camera);

public:
	
	int ramification;
	SDL_Rect				Quadrant;
	list<ImageRender*>	Objects;
	array<Quadtree*,4>		ramifications;

};
#endif // !__QUADTREE_H__

