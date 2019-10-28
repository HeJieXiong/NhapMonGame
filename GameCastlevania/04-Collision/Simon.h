#pragma once
#include "GameObject.h"
#include "Morningstar.h"
#include "Knife.h"
#include "HeaderBar.h"
#include "Stair.h"
#include "Ghost.h"
#include"debug.h"
#include "Brick.h"
#define SIMON_WALKING_SPEED		0.1f 
//0.1f
#define SIMON_JUMP_SPEED_Y		0.4f
#define SIMON_JUMP_SPEED_X		0.1f
#define SIMON_STAY_JUMP_SPEED_Y		0.05f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_GRAVITY_ON_STAIR_Y			0.004f
#define SIMON_GRAVITY_ON_STAIR_X			0.004f
#define SIMON_GRAVITY_DOWN_STAIR_Y			0.004f
#define SIMON_GRAVITY_DOWN_STAIR_X			0.004f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_SIT_LOCATION 100

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT_DOWN		500
#define SIMON_STATE_ATTACK			600
#define SIMON_STATE_DISAPPEAR		700
#define SIMON_STATE_ON_STAIR		800
#define SIMON_STATE_EXTRA			900

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
#define SIMON_ANI_DISAPPEAR			14
#define SIMON_ANI_ON_STAIR_LEFT		15
#define SIMON_ANI_ON_STAIR_RIGHT	16
#define SIMON_ANI_DOWN_STAIR_LEFT	17
#define SIMON_ANI_DOWN_STAIR_RIGHT	18

#define SIMON_ANI_STAY_STAIR_LEFT_DOWN	19
#define SIMON_ANI_STAY_STAIR_LEFT_UP	20
#define SIMON_ANI_STAY_STAIR_RIGHT_DOWN	21
#define SIMON_ANI_STAY_STAIR_RIGHT_UP	22
#define SIMON_ANI_STAY_EXTRA_LEFT	23
#define SIMON_ANI_STAY_EXTRA_RIGHT	24
#define SIMON_ANI_DIE				25
#define SIMON_BIG_BBOX_WIDTH  14
#define SIMON_BIG_BBOX_HEIGHT 32
#define SIMON_SIT_BBOX_WIDTH  20
#define SIMON_SIT_BBOX_HEIGHT 30

#define SIMON_UNTOUCHABLE_TIME 1000
#define SIMON_ATTACK_TIME 300
#define SIMON_JUMP_TIME 300
#define SIMON_WALKING_TIME 400
#define SIMON_TAKING_TIME 3000
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 260

class CSimon : public CGameObject
{
	int level;
	int untouchable;
	float attack_time = 0;
	float walking_time = 0;
	int attacking;
	float jump_time = 0;

	DWORD untouchable_start;
	DWORD attack_start;
	DWORD walking_start;
	CMorningstar *morningstar;
	CKnife	*knife;
	CHeaderBar *headerbar;
	DWORD jump_start;


public: 
	vector<LPGAMEOBJECT> objects_weapons;
	int attack_wp;
	int combine_array = 0;
	float test_val;
	bool isFalling=true;
	int has_wp=0; //Dùng để kiểm tra Simon đã nhặt được item phóng được chưa.
	int is_walking; //Biến dùng để kiểm tra xem Simon có đang trong trạng thái tự động đi chưa
	int is_on_stair; //Kiểm tra Simon có va chạm với các box cầu thang chưa.
	int has_g=1; //1 có trọng lực 0 ko có trọng lực
	int state_direction_on_stair;
	int between_stair = 0;
	int point=0;
	int walking_up = 0; // giá trị 1 là đang đi lên
	int is_sit = 1;
	int nx_knife;
	int on_jump;
	int jump_walk = 0;
	int state_extra = 0;
	float take_item_start = 0;
	float taking_time = 0;
	int taking_jump = 0;
	int attack_then_walk = 0;
	CSimon(CMorningstar *a, CHeaderBar *b, CKnife *c) : CGameObject()
	{
		morningstar = a;
		headerbar = b;
		knife = c;
		untouchable = 0;
		nx_knife = nx;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StarAttack() { attacking = 1; attack_start = GetTickCount(); }
	void Attack(CMorningstar *monringstar,float &x_cam, float &y_cam);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Attack_Weapons();
	void Walking_on_stair();
	void Walking_down_stair();
};