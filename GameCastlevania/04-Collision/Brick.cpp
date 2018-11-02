#include "Brick.h"

void CBrick::Render(float &xcam, float &ycam )
{
	animations[0]->Render(x-xcam, y-ycam);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}