#include <algorithm>
#include "debug.h"

#include "Background.h"
#include "Game.h"


#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"



void CBackGround::Render()
{
	int ani;
	ani = BACK_GROUND_ANI;
	int alpha = 255;
	animations[ani]->Render(x, y, alpha);
}



void CBackGround::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BACK_GROUND_BBOX_WIDTH;
	bottom = y + BACK_GROUND_BBOX_HEIGHT;
}

