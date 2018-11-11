#pragma once
#include "GameObject.h"

#define MORNINGSTAR_NORMAL		0
#define MORNINGSTAR_TYPE_SHORT	1
#define MORNINGSTAR_TYPE_LONG	2
#define MORNINGSTAR_BOX_WIDTH	50
#define MORNINGSTAR_BOX_HEIGHT	10
#define ID_TEX_MORNINGSTAR 40

class CMorningstar : public CGameObject {
private:
	static CMorningstar * _instance;	
	int type_morningstar;
public:
	CMorningstar();
	~CMorningstar();
	static CMorningstar * GetInstance();
	void LoadResource();
	virtual void SetType(int type);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

