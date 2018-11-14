#pragma once
#include "GameObject.h"
#include "Item.h"
#define FIRE_STATE 100
#define FIRE_ANI 0
#define FIRE_BOX_WIDTH 17
#define FIRE_BOX_HEIGHT 31
class CFire : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	CItem *Item;

public:
	/*CFire(CItem *a) :CGameObject() {
		Item = a;
	}*/
	int state=0;
	virtual void SetState(int state);
};