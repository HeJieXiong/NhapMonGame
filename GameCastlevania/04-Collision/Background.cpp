#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "Background.h"




void CBackGround::Render(float &xcam, float &ycam)
{
	int ani;
	ani = BACK_GROUND_ANI;
	int alpha = 255;
	animations[ani]->Render(x-xcam, y-ycam, alpha);
}
void CBackGround::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BACK_GROUND_BBOX_WIDTH;
	bottom = y + BACK_GROUND_BBOX_HEIGHT;
}




