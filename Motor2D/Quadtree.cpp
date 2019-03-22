#include "Quadtree.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Colliders.h"


void Quadtree::Clear()
{
	//First we have to clear all the objects of the node
	list<ImageRender*>::iterator item = Objects.begin();

	for (item;item!=Objects.end();item++)
	{
		if (*item == nullptr)
		{
			RELEASE(*item);
		}
	}
	
	Objects.clear();

	//Now we have to call all the children of the node and check if they have also childre 
	for (int i = 0; i < ramifications.size(); i++){
		if (ramifications[i] != nullptr){
			ramifications[i]->Clear();
			ramifications[i] = nullptr;
		}
	}
}

void Quadtree::Split() {
	int x = this->Quadrant.x;
	int y = this->Quadrant.y;
	int w = (int)(this->Quadrant.w / 2);
	int h = (int)(this->Quadrant.h / 2);
	ramifications[0] = new Quadtree({ x, y, w, h }, ramification +1);
	ramifications[1] = new Quadtree({ x + w, y, w, h }, ramification +1);
	ramifications[2] = new Quadtree({ x, y + h, w, h }, ramification + 1);
	ramifications[3] = new Quadtree({ x + w, y + h, w, h }, ramification + 1);
}

int Quadtree::getIndex(const SDL_Rect& r){
	int index = -1;
	float MidWeight = Quadrant.x+(Quadrant.w/2);
	float MidHeight = Quadrant.y+(Quadrant.h/2);
	bool TopChildren = (r.y < MidHeight && r.y+r.h<MidHeight);
	bool BottomChildren = (r.y > MidHeight);
	if (r.x < MidWeight && r.x + r.w < MidWeight){
		if (TopChildren){
			index = 0;
		}else if(BottomChildren){
			index = 2;
		}
	}else if (r.x > MidWeight){
		if (TopChildren){
			index = 1;
		}else if(BottomChildren){
			index = 3;
		}
	}
	return index;
}

bool Quadtree::insert(ImageRender* obj){
	//TODO 3: Create the insert function
	if (obj == nullptr){
		return false;
	}
	if (IfInside(obj->rect) == false){
		return false;
	}
	if (ramifications[0] != nullptr){
		int in = getIndex(obj->rect);
		if (in != - 1){
			ramifications[in]->insert(obj);
		}
		return true;
	}
	Objects.push_back(obj);
	if (Objects.size() > 1 && ramification<MAX_RAMIFICATIONS){
		if (ramifications[0] == nullptr){
			Split();
		}
		for (list<ImageRender*>::iterator item = Objects.begin(); item != Objects.end(); item++){
			int index = getIndex((*item)->rect);
			if (index != -1){
				ramifications[index]->insert(*item);
				Objects.remove(*item);
			}
		}
	}
	return true;	
}

vector<ImageRender*> Quadtree::PushCollisionVector(vector<ImageRender*> &ObjList, const SDL_Rect& camera)
{
	if (ramifications[0] != nullptr)
	{
		int in = getIndex(camera);
		if (in != -1){
			ramifications[in]->PushCollisionVector(ObjList, camera);
		}else{
			for (int i = 0; i < 4; ++i){
				ramifications[i]->PushCollisionVector(ObjList,camera);
			}
		}
	}
	
	for (list<ImageRender*>::iterator item = Objects.begin(); item != Objects.end(); item++){
		ObjList.push_back(*item);
	}

	return ObjList;
}

bool Quadtree::IfInside(const SDL_Rect& r){
	if (Quadrant.x < r.x + r.w && Quadrant.x + Quadrant.w > r.x){
		if (Quadrant.y < r.y + r.h && Quadrant.y + Quadrant.h > r.y){
			return true;
		}
	}
	return false;
}


void Quadtree::QuadDrawer(){
	if (ramifications[0] != nullptr){
		for (int i = 0; i < 4; ++i){
			ramifications[i]->QuadDrawer();
		}
	}else{
		App->render->DrawQuad(Quadrant, 255, 255, 255, 255, false);
	}
}
