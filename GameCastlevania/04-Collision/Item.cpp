#include "Item.h"

void CItem::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x ;
	bottom = y;
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CItem::Render(float &xcam, float &ycam, float &x_, float &y_)
{
	int ani = 1;
	float a = 50;
	animations[ani]->Render(a,a);
	//RenderBoundingBox(xcam, ycam);
}

void CItem::SetState(int state)
{
	CGameObject::SetState(state);
	//switch (state)
	//{
	//case FIRE_STATE:
	//	x += 100;
	//	y = 100;
	//	vx = 0;
	//	vy = 0;
	//	break;
	//}
}