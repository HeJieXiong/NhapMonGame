#pragma once
#include "GameObject.h"
#define STAIR_HEIGHT 15;
#define STAIR_WIDTH	 40;
#define STAIR_BIG_HEIGHT 15;
#define STAIR_BIG_WIDHT 80;
class CStair : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
public:
	int id; 
	bool check_stair;
	int type_stair; //Dùng để kiểm tra xem nếu là stair 1 sẽ là đi lên còn stair 2 sẽ là đi xuống
	int stair_direction; //Dùng để kiểm tra hướng cầu thang mà Simon đang đứng: 1 là phải lên 2 là phải xuống 3 trái lên 4 trái xuống 
	int is_big;
	int center;
	virtual void Render(float &xcam, float &ycam, float &x_, float &y_);
};