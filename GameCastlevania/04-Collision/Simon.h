#pragma once
#include "GameObject.h"
#include "Morningstar.h"

#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.4f
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
#define SIMON_STATE_ATTACK			600

#define SIMON_ANI_BIG_IDLE_RIGHT	0
#define SIMON_ANI_BIG_IDLE_LEFT		1
#define SIMON_ANI_SMALL_IDLE_RIGHT	2
#define SIMON_ANI_SMALL_IDLE_LEFT	3

#define SIMON_ANI_BIG_WALKING_RIGHT	4
#define SIMON_ANI_BIG_WALKING_LEFT	5
#define SIMON_ANI_JUMP_RIGHT		6
#define SIMON_ANI_JUMP_LEFT			7
#define SIMON_ANI_SIT_DOWN_LEFT		8
#define SIMON_ANI_SIT_DOWN_RIGHT	9
#define SIMON_ANI_ATTACK_LEFT		10
#define SIMON_ANI_ATTACK_RIGHT		11
#define SIMON_ANI_SIT_ATTACK_LEFT	12
#define SIMON_ANI_SIT_ATTACK_RIGHT	13
#define SIMON_ANI_DIE				14
#define SIMON_BIG_BBOX_WIDTH  20
#define SIMON_BIG_BBOX_HEIGHT 30

#define SIMON_UNTOUCHABLE_TIME 1000
#define SIMON_ATTACK_TIME 2000
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

class CSimon : public CGameObject
{
	int level;
	int untouchable;
	int attack_time = 0;
	int attacking;
	DWORD untouchable_start;
	DWORD attack_start;
	CMorningstar *morningstar;
public: 
	CSimon() : CGameObject()
	{
		untouchable = 0;
		morningstar = CMorningstar::GetInstance();
	}
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StarAttack() { attacking = 1; attack_start = GetTickCount(); }
	void Attack(float &x_cam, float &y_cam);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

};