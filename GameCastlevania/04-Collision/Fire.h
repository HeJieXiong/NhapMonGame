#pragma once
#include "GameObject.h"
#define FIRE_STATE 100
#define FIRE_ANI 0
#define FIRE_BOX_WIDTH 10
#define FIRE_BOX_HEIGHT 30
class CFire : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float  &ycam);


public:
	virtual void SetState(int state);
};