#pragma once
#include "GameObject.h"
#include "Item.h"
#define LGIHT_STATE 100
#define LIGHT_ANI 0
#define LIGHT_BOX_WIDTH 20
#define LIGHT_BOX_HEIGHT 19
#define LIGHT_GRAVITY 0.0002f
class CLight : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);

public:
	int state = 0;
	float time_start;
	float time_disappear = 0;
	virtual void SetState(int state);
	void Light_setting(CLight *Light, float &x, float &y);
	int ready = 0;
};