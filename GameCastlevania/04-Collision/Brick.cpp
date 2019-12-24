#include "Brick.h"

void CBrick::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	animations[0]->Render(x-xcam, y-ycam);
	RenderBoundingBox(xcam,ycam);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	if (type == 0 ||type ==15) {
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
	else if (type == 10) {
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_EFECT_BBOX_HEIGHT;
	}
	else {
		r = x + BIG_BRICK_BBOX_WIDTH;
		b = y + BIG_BRICK_BBOX_HEIGHT;
	}
}

//bool CBrick::check() {
//	return FALSE;
//}