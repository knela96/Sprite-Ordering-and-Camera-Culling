#ifndef __Prop__H_
#define __Prop__H_

#include "j1EntityManager.h"
#include "Entity.h"

class Prop:public Entity
{
public:
	Prop(int x, int y, entitytype type);
	~Prop();

	bool Update(float dt);

private:

	uint height;
	uint width;

};

#endif // !__Prop__H_
