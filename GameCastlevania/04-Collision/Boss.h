#pragma once
#include "GameObject.h"
#include "Simon.h"


#define BOSS_BBOX_WIDTH		48
#define BOSS_BBOX_HEIGHT	23
#define BOSS_SPEED_X		0.02f
#define BOSS_SPEED_Y		0.02f
#define BOSS_ATK_SPEED_X	0.5f
#define BOSS_ATK_SPEED_Y	0.5f
#define BOSS_STATE_STANDING	100
#define BOSS_STATE_FLY		200
#define BOSS_STATE_DIE		300

#define BOSS_ANI_STANDING	0
#define BOSS_ANI_FLY		1
#define BOSS_ANI_DIE		2
#define PI 3.14
class CBoss :
	public CGameObject
{
	LPGAMEOBJECT *item;
	bool reachRandPoint;
	bool isAttacking;
	bool reachTarget;
	D3DVECTOR *destination;
	D3DVECTOR *target;
	DWORD attackTime;
	DWORD burnTime;
	bool isDying;
	static CBoss *instance;
	CSimon *simon;
	float flying_coordinate;//tọa độ được cộng thêm của dơi
public:
	int curHealth;
	int check_fly;//check_fly=0 bay ngang, check_fly =1 bay zic_zac,check_fly=2 boss standing
	CBoss();
	CBoss(CSimon *a) : CGameObject()
	{
		check_fly = 2;
		simon = a;
	}
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	~CBoss();
};
