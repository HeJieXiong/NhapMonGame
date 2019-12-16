#include "Stair.h"

void CStair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	if (is_big == 0) {
		right = x + STAIR_WIDTH;
		
	}
	if (is_big == 1) {
		right = x + STAIR_WIDTH_SMALL;
	}
	bottom = y + STAIR_HEIGHT;
	center = x +(right-x)/2;
	if (type_stair == 2|| type_stair == 10 || type_stair == 100) {
		head = x;
		tail = right;
	}
	if (type_stair == 4) {
		head = right;
	}
	if (type_stair == 100) { // stair_change
		tail = right;
	}
}

void CStair::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CStair::Render(float & xcam, float & ycam, float & x_, float & y_)
{
RenderBoundingBox(xcam, ycam);
}
