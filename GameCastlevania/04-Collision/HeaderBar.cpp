#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "HeaderBar.h"




void CHeaderBar::Render(float &xcam, float &ycam)
{
	int ani;
	ani = HEADER_BAR_ANI;
	int alpha = 255;
	animations[ani]->Render(x, y, alpha);
}
void CHeaderBar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + HEADER_BAR_BBOX_WIDTH;
	bottom = y + HEADER_BAR_BBOX_HEIGHT;
}



