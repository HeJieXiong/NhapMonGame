#include "Bat.h"
#include "GameObject.h"
#include <math.h>
#include "Debug.h""


void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	/*if (is_active == true) {*/
	if (simon->touch_wake == 1)
	{
		is_active = true;
	}
	if (is_active == true) {
		if (vx < 0) {
			if (x < 0) {
				SetState(BAT_STATE_FLY_RIGHT);
			}
			else {
				SetState(BAT_STATE_FLY_LEFT);
			}
		}
		if (vx > 0 ) {
			if (x > 450) {
				SetState(BAT_STATE_FLY_LEFT);
			}
			else SetState(BAT_STATE_FLY_RIGHT);
		}	
		if (y != BAT_Y_DIS) {
			y = 10 * sin(flying_coordinate* PI / 180) + bat_x;
			x += dx;
			flying_coordinate += 5;
		}
	}
	// Xét va chạm của bat và Simon
	
	if (nx>0){
		if (x + BAT_BBOX_WIDTH >= simon->x &&x <= simon->x && y+ BAT_BBOX_HEIGHT >= simon->y && y <= simon->y) {
			if (simon->untouchable == 0 && simon->is_heart == 0) {
				simon->start_heart = GetTickCount();
				simon->is_heart = 1;
				simon->state = SIMON_STATE_HEART;
			}
			else {
				x += dx;
			}
		}
	}
	if (nx < 0) {
		if (x + BAT_BBOX_WIDTH >= simon->x+SIMON_BIG_BBOX_WIDTH &&x <= simon->x + SIMON_BIG_BBOX_WIDTH 
			&& y <= simon->y+ SIMON_BIG_BBOX_WIDTH &&  y + BAT_BBOX_HEIGHT >= simon->y+ SIMON_BIG_BBOX_WIDTH) {
			if (simon->untouchable == 0 && simon->is_heart == 0) {
				simon->start_heart = GetTickCount();
				simon->is_heart = 1;
				simon->state = SIMON_STATE_HEART;
			}
			else {
				x += dx;
			}
		}
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	//simon->point += this->point;
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			/*if (dynamic_cast<StartPoint *>(e->obj))
			{
				StartPoint *start = dynamic_cast<StartPoint *>(e->obj);
				if (jumped != true)
				{
					SetState(DOG_STATE_JUMP);
					return;
				}
			}*/
			if (dynamic_cast<CKnife *>(e->obj))
			{
				CKnife *knife = dynamic_cast<CKnife *>(e->obj);
				y = BAT_Y_DIS;
				vy = 0;
				knife->y = 1000;
				knife->vx = 0;
			}
		}
	}
}

void CBat::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	int ani = 0;
	if (nx == 1) {
		ani = BAT_ANI_FLY_RIGHT;
	}
	else
		ani = BAT_ANI_FLY_LEFT;
	animations[ani]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);
	//RenderBoundingBox();
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_FLY_LEFT:
		nx = -1;
		vx = -BAT_SPEED;
		break;
	case BAT_STATE_FLY_RIGHT:
		nx = 1;
		vx = BAT_SPEED;
		break;
	}
}
