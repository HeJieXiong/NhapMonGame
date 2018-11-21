#pragma once
#include "GameObject.h"

#define MORNINGSTAR_NORMAL_LEFT		0
#define MORNINGSTAR_NORMAL_RIGHT	1
#define MORNINGSTAR_TYPE_1_LEFT		2
#define MORNINGSTAR_TYPE_1_RIGHT	3
#define MORNINGSTAR_BOX_WIDTH	46
#define MORNINGSTAR_BOX_HEIGHT	8
#define MORNINGSTAR_ATTACK_TIME 60
#define TYPE_1_BOX_HEIGHT 8
#define TYPE_1_BOX_WIDTH 60

class CMorningstar : public CGameObject {
private:
	static CMorningstar * _instance;	
	int type_morningstar;
	DWORD attack_start;
	int attack_time = 0;
public:
	CMorningstar();
	~CMorningstar();
	static CMorningstar * GetInstance();
	int state;
	void Update_colison(vector<LPGAMEOBJECT> *coObjects);
	virtual void SetType(int a);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

