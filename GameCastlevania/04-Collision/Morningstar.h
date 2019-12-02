#pragma once
#include "GameObject.h"

#define MORNINGSTAR_NORMAL_LEFT		0
#define MORNINGSTAR_NORMAL_RIGHT	1
#define MORNINGSTAR_TYPE_1_LEFT		2
#define MORNINGSTAR_TYPE_1_RIGHT	3
#define MORNINGSTAR_TIME_COUNT	1
#define MORNINGSTAR_TIME_CHECK	25
#define MORNINGSTAR_BOX_WIDTH	46
#define MORNINGSTAR_BOX_HEIGHT	8
#define MORNINGSTAR_ATTACK_TIME 300
#define TYPE_1_BOX_HEIGHT 8
#define TYPE_1_BOX_WIDTH 60

class CMorningstar : public CGameObject {
private:
	static CMorningstar * _instance;	
	int type_morningstar;
	
	
public:
	CMorningstar();
	~CMorningstar();
	static CMorningstar * GetInstance();
	float attack_time = 10;
	int state;
	int attacked=2;
	int isLastFrame = 0;
	int attack_on_stair = 0;
	DWORD attack_start;
	DWORD start_last_frame;
	//void Update_colison(vector<LPGAMEOBJECT> *coObjects);
	virtual void SetType(int a);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

