#include "Stair.h"

void CStair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + STAIR_WIDTH;
	bottom = y + STAIR_HEIGHT;
}

void CStair::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CStair::Render(float & xcam, float & ycam, float & x_, float & y_)
{
	//RenderBoundingBox(xcam, ycam);
}
