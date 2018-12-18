#pragma once
#include "GameObject.h"
#include  "Simon.h"

#define FISH_STATE_WALKING_LEFT		100
#define FISH_STATE_WALKING_RIGHT	200
#define FISH_STATE_JUMP_LEFT		300
#define FISH_STATE_JUMP_RIGHT		400
#define FISH_STATE_ATK_LEFT			500
#define FISH_STATE_ATK_RIGHT		600
#define FISH_STATE_HIDE				700

#define FISH_ANI_WALKING_LEFT		0
#define FISH_ANI_WALKING_RIGHT		1
#define FISH_ANI_JUMP_LEFT			2
#define FISH_ANI_JUMP_RIGHT			3
#define FISH_ANI_ATK_LEFT			4
#define FISH_ANI_ATK_RIGHT			5
#define FISH_ANI_HIDE				6


#define FISH_JUMP_SPEED				0.5f
#define FISH_GRAVITY				0.002f
#define FISH_WALKING_SPEED			0.05f

#define FISH_BBOX_WIDTH				40
#define FISH_BBOX_HEIGHT			60
#define BULLET_BBOX_WIDTH			14
#define BULLET_BBOX_HEIGHT			12
#define FISH_ATTACK_RANGE			400
#define FISH_DETECT_RANGE			134
#define FISH_BULLET_SPEED_X			0.2f
#define WATER_HEIGHT				64*5+32
class CBullet : public CGameObject
{
public:
	CBullet();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CBullet();
};
class CFish :
	public CGameObject
{
	CSimon *simon;
	bool goingUp;
	bool isAttacking;
	CBullet *bullet;
	LPGAMEOBJECT heart;
	DWORD attackTime;
	int attackStart;
	int hitWater;
	
public:
	CFish(CSimon *a) : CGameObject()
	{
		simon = a;
		bullet = NULL;
	}
	CFish();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	//void SetNumofDrop(int num);
	void AddItem(LPGAMEOBJECT item) { heart = item; };
	~CFish();
};