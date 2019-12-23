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
#define FISH_STATE_JUMP_DOWN		800

#define FISH_ANI_WALKING_LEFT		0
#define FISH_ANI_WALKING_RIGHT		1
#define FISH_ANI_JUMP_LEFT			2
#define FISH_ANI_JUMP_RIGHT			3
#define FISH_ANI_ATK_LEFT			4
#define FISH_ANI_ATK_RIGHT			5
#define FISH_ANI_HIDE				6


#define FISH_JUMP_SPEED				0.1f
#define FISH_GRAVITY				0.002f
#define FISH_WALKING_SPEED			0.01f
#define FISH_WALKING_SPEED_HIGH			0.5f
#define FISH_BBOX_WIDTH				15
#define FISH_BBOX_HEIGHT			29.5
#define BULLET_BBOX_WIDTH			10
#define BULLET_BBOX_HEIGHT			10
#define FISH_ATTACK_RANGE			400
#define FISH_DETECT_RANGE			134
#define FISH_BULLET_SPEED_X			0.02f
#define WATER_HEIGHT				64*5+32
#define FISH_TIME_JUMP_DOWN			1100
#define FISH_ATTACK_RANGE			400
#define STATE_FOR_CHANGE			70
class FishBullet : public CGameObject
{
public:
	CSimon *simon;
	FishBullet(CSimon *a) : CGameObject()
	{
		simon = a;
		tag = 17;
		is_active = true;
		this->AddAnimation(2001);
		this->AddAnimation(2002);
		ani_bullet = 0;
	}
	int ani_bullet = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~FishBullet();
};
class CFish :
	public CGameObject
{
	CSimon *simon;
	bool isAttacking;
	FishBullet *bullet;
	LPGAMEOBJECT heart;
	DWORD attackTime;
	int attackStart;
	int hitWater;
	int is_standing;
	int is_walking;
	DWORD start_jump;
	DWORD fire_countdown;
	int can_count = 1;
	int is_jump = 0;
	int falling_down = 1;
	int first_touch = 0;
	int change_way = 0;
	int jump_down = 0;
	int touch_ground = 0;
	float x_bullet;
	int bullet_way = 0;
public:
	CFish(CSimon *a) : CGameObject()
	{
		simon = a;
		bullet = NULL;
		vy = 0;
		is_standing = 0;
		
		
	}
	int can_fire = 0;
	int code = 0;
	float center;
	CFish();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	//void SetNumofDrop(int num);
	void AddItem(LPGAMEOBJECT item) { heart = item; };
	~CFish();
};