#pragma once
#include "GameObject.h"

#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_SIT_LOCATION 100

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT_DOWN		500

#define SIMON_ANI_BIG_IDLE_RIGHT		0
#define SIMON_ANI_BIG_IDLE_LEFT			1
#define SIMON_ANI_SMALL_IDLE_RIGHT		2
#define SIMON_ANI_SMALL_IDLE_LEFT			3

#define SIMON_ANI_BIG_WALKING_RIGHT			4
#define SIMON_ANI_BIG_WALKING_LEFT			5
#define SIMON_ANI_JUMP_RIGHT		6
#define SIMON_ANI_JUMP_LEFT		7
#define SIMON_ANI_SIT_DOWN_LEFT		8
#define SIMON_ANI_SIT_DOWN_RIGHT	9
#define SIMON_ANI_DIE				10

#define	SIMON_LEVEL_SMALL	1
#define	SIMON_LEVEL_BIG		2

#define SIMON_BIG_BBOX_WIDTH  20
#define SIMON_BIG_BBOX_HEIGHT 30

#define SIMON_UNTOUCHABLE_TIME 5000


class CSimon : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
public: 
	CSimon() : CGameObject()
	{
		untouchable = 0;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};