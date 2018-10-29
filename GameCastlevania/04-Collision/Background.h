#pragma once
#include "GameObject.h"

#define BACK_GROUND_STATE 100
#define BACK_GROUND_ANI 0
#define BACK_GROUND_BBOX_WIDTH  400
#define BACK_GROUND_BBOX_HEIGHT 600
class CBackGround : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
public:
	CBackGround() : CGameObject()
	{
		untouchable = 0;
	}
	/*virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);*/
	virtual void Render();
	/*void SetState(int state);*/
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
