#pragma once
#include "GameObject.h"
#define ITEM_HEART 1
#define ITEM_HEART_BIG 2
class CItem : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);


public:
	virtual void SetState(int state);
};