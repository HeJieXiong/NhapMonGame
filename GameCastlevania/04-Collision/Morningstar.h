#pragma once
#include "GameObject.h"

#define MORNINGSTAR_NORMAL		0
#define MORNINGSTAR_TYPE_SHORT	1
#define MORNINGSTAR_TYPE_LONG	2
#define MORNINGSTAR_BOX_WIDTH	46
#define MORNINGSTAR_BOX_HEIGHT	8


class CMorningstar : public CGameObject {
private:
	static CMorningstar * _instance;	
	int type_morningstar;
public:
	CMorningstar();
	~CMorningstar();
	static CMorningstar * GetInstance();
	int state;
	float x_current;
	float y_current;
	void Update_colison(vector<LPGAMEOBJECT> *coObjects);
	virtual void SetType(int type);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

