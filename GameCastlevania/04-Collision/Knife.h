#pragma once
#include "GameObject.h"
#include "Fire.h"
#include "Candle.h"

#define KNIFE_NORMAL_LEFT		0
#define KNIFE_NORMAL_RIGHT	1
#define KNIFE_ATTACK_TIME 60
#define KNIFE_BOX_HEIGHT 8
#define KNIFE_BOX_WIDTH 20
#define KNIFE_GRAVITY 0.02f
class CKnife : public CGameObject {
private:
	static CKnife * _instance;
	int type_morningstar;
	DWORD attack_start;
	int attack_time = 0;
public:
	CKnife();
	~CKnife();
	static CKnife * GetInstance();
	int state;
	int is_fly = 0;
	void Update(DWORD dt,vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

