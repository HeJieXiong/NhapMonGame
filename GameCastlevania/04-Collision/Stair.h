#pragma once
#include "GameObject.h"
#define STAIR_HEIGHT 16;
#define STAIR_WIDTH	 8;
class CStair : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);



public:
	bool check_stair;
	int type_stair; //Dùng để kiểm tra xem nếu là stair 1 sẽ là đi lên còn stair 2 sẽ là đi xuống
	int stair_direction; //Dùng để kiểm tra hướng cầu thang 1 là phải 2 là trái
	virtual void Render(float &xcam, float &ycam, float &x_, float &y_);
};