#pragma once
#include "GameObject.h"

#define GHOST_WALKING_SPEED 0.05f;

#define GHOST_BBOX_WIDTH 16
#define GHOST_BBOX_HEIGHT 31

#define GHOST_STATE_WALKING 100
#define GHOST_STATE_DIE 200

#define GHOST_ANI_WALKING 0
class CGhost : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);


public:
	virtual void SetState(int state);
};