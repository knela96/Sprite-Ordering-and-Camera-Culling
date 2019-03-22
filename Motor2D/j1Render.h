#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include <queue>
#include <vector>
#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Quadtree.h"
#include "j1PerfTimer.h"

using namespace std;
class ImageRender
{
public:

	ImageRender(uint order, uint height,SDL_Texture* texture, int x, int y, const SDL_Rect* section, float scale, float speed, double angle, int pivot_x, int pivot_y, SDL_Rect rect) :
		order(order),height(height),tex(texture), x(x), y(y), section(section), scale(scale), speed(speed),angle(angle),pivot_x(pivot_x), pivot_y(pivot_y),rect(rect){}

	uint Ordering()const
	{
		return order;
	}

public:
	SDL_Texture*		tex;
	int					x;
	int					y;
	const SDL_Rect*		section;
	SDL_Rect			rect;
	float				scale;
	float				speed;
	double				angle;
	int					pivot_x;
	int					pivot_y;

	uint				order;
	uint				height;
};

struct Comparer
{
	bool operator()(const ImageRender* img1, const ImageRender* img2)const
	{
		return img1->Ordering() > img2->Ordering();
	}
};

class j1Render : public j1Module
{
public:

	j1Render();
	virtual ~j1Render();
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	void reOrder();
	bool PostUpdate();
	bool CleanUp();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	//void Push(uint order,SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float scale = 1.0f, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX);
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float scale = 1.0f, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	void Push(uint order, uint height, SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float scale = 1.0f, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX);
	bool OrderBlit(priority_queue <ImageRender*, vector<ImageRender*>, Comparer>& Queue)const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool InsideCamera(const SDL_Rect& rect)const;
	void PushVector(uint order, uint height, SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float scale = 1.0f, float speed = 1.0f, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX);
	void j1Render::PushFromVector(vector<ImageRender*> sprites);
	void checkOrder(vector<ImageRender*>& sprites);
	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer*	renderer = nullptr;
	SDL_Rect		camera;
	SDL_Rect		viewport;
	SDL_Color		background;
	vector<ImageRender*> Images;
	priority_queue <ImageRender*,vector<ImageRender*>, Comparer> OrderToRender;
	j1PerfTimer timer;
	list< ImageRender*> map_sprites;
	list< ImageRender*> entities_sprites;

private:

	bool	FullMap;
	Quadtree* tree;
};

#endif // __j1RENDER_H__