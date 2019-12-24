#include "Panther.h"
#include "Simon.h"

//CPanther::CPanther()
//{
//	
//}
void CPanther::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += PANTHER_GRAVITY * dt;
	if (simon->touch_wake ==1)
	{
		if (code == 1) {
			is_standing = false;
			is_active = true;
		}
		
	}
	if (simon->touch_wake == 2)
	{
		if (code == 2) {
			simon->count_panther_code = code;
			is_standing = false;
			is_active = true;
		}
	}
	// Xét va chạm của panther và Simon
	if (x+ PANTHER_BBOX_WIDTH >= simon->x && x + PANTHER_BBOX_WIDTH <= simon->x+ SIMON_SIT_BBOX_WIDTH && y+ PANTHER_BBOX_HEIGHT >= (simon-> y +SIMON_SIT_BBOX_HEIGHT)
		&& y <= (simon->y + SIMON_SIT_BBOX_HEIGHT)) {
		if (simon->untouchable == 0&& simon->is_heart==0) {
			simon->start_heart = GetTickCount();
			simon->is_heart = 1;
			simon->state = SIMON_STATE_HEART;
		
		}
		else {
			x += dx;
		}
	}
	/*if (is_standing == false)
	{*/
		//if(is_jump==1)
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
				if (dynamic_cast<CBrick *>(e->obj))
				{
					CBrick *ground = dynamic_cast<CBrick *>(e->obj);
					if (is_standing == 0) {
						if (ground->y <=200)
						{
							SetState(PANTHER_STATE_WALKING_LEFT);
						}
						else SetState(PANTHER_STATE_WALKING_RIGHT);
					}
					else SetState(PANTHER_STATE_SLEEP);
				}
				if (dynamic_cast<CStair *>(e->obj))
				{
					CStair *stair = dynamic_cast<CStair *>(e->obj);
					if (is_jump == 1)
					{
						SetState(PANTHER_STATE_WALKING_LEFT);
					}
					else SetState(PANTHER_STATE_WALKING_RIGHT);
					if (stair->type_stair == 50) {
						x = -9999;
						vy = 0;
						vx = 0;
					}
				}
				if (dynamic_cast<CKnife *>(e->obj))
				{
					CKnife *knife = dynamic_cast<CKnife *>(e->obj);
					y = PANTHER_Y_DIS;
					vy = 0;
					knife->y = 1000;
					knife->vx = 0;
				}
			}
		}
	if (y == PANTHER_Y_DIS) {
		vy = 0;
	}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

		}
	
	/*DebugOut(L"Panther_a %f\n", a);
	DebugOut(L"Panther_act %f\n", this->is_active);
	DebugOut(L"state %f\n", this->state);
	DebugOut(L"Jump %f\n", this->is_jump);
	DebugOut(L"vx %f\n", this->vx);*/
}

void CPanther::Render(float & xcam, float & ycam, float & x_simon, float & y_simon)
{
	/*
	if (is_active == true)
	{*/
		int ani = 0;
			if (vx == 0)
				ani = PANTHER_ANI_SLEEP;
			if (state == PANTHER_STATE_JUMP)
				ani = PANTHER_ANI_JUMP_LEFT;
			if (vx > 0)
				ani = PANTHER_ANI_WALKING_RIGHT;
			if (vx < 0)
				ani = PANTHER_ANI_WALKING_LEFT;
		

		animations[ani]->Render(x - xcam, y - ycam);
		RenderBoundingBox(xcam, ycam);
	/*}*/
}

void CPanther::SetState(int state)
{
	CGameObject::SetState(state);
		switch (state)
		{
		case PANTHER_STATE_JUMP:
			//vy = -PANTHER_WALKING_SPEED_Y;
			vx = -PANTHER_WALKING_SPEED_X;
			is_jump = 1;
			break;
		case PANTHER_STATE_SLEEP:
			nx = -1;
			is_standing = 1;
			vx = 0;
			break;
		case PANTHER_STATE_WALKING_LEFT:
			nx = -1;
			vx = -PANTHER_WALKING_SPEED_X;
			break;
		case PANTHER_STATE_WALKING_RIGHT:
			nx = 1;
			vx = +PANTHER_WALKING_SPEED_X;
			break;
		}
	}

