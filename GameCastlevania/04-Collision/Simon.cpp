﻿#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"
#include "Morningstar.h"
void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state!=SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	/*if ( GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}*/
	if (attacking == 1) {
		if (GetTickCount() - attack_start >SIMON_ATTACK_TIME)
		{
			state = SIMON_STATE_ATTACK;
			attack_time++;
		}
	}
	if (attack_time > 25) {
		attacking = 0;
		attack_time = 0;
	}
	if (coEvents.size() == 0)//new code
	{
		x += dx;
		if (y >0) {
			y += dy;
		}
		else {
			y += 0.4f;
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty*dy + ny*0.4f;
		
		if (nx!=0) vx = 0;
		if (ny!=0) vy = 0;	
	}
/*	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];	
		if (attacking == 1) {
			StarAttack();
		}
	}*/

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render(float &xcam, float  &ycam)
{
	int ani;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	if (state == SIMON_STATE_SIT_DOWN) {
		if (nx < 0) {
			ani = SIMON_ANI_SIT_DOWN_LEFT;
		}
		else ani= SIMON_ANI_SIT_DOWN_RIGHT;
	}
	else if (state == SIMON_STATE_ATTACK) {
				if (level == 1) {
					if (nx < 0) {
						ani = SIMON_ANI_SIT_ATTACK_LEFT;
					}
					else ani = SIMON_ANI_SIT_ATTACK_RIGHT;
				}
				if (level == 0) {
					if (nx < 0) {
						ani = SIMON_ANI_ATTACK_LEFT;
					}
					else ani = SIMON_ANI_ATTACK_RIGHT;
				}
	}
	else{		
		if (vx == 0){
			if (nx>0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
			else if(nx<0) ani = SIMON_ANI_BIG_IDLE_LEFT;
		}
		else if (vx > 0) 
			ani = SIMON_ANI_BIG_WALKING_RIGHT; 
		else ani = SIMON_ANI_BIG_WALKING_LEFT;
		if (vy < 0) {
			if (nx>0) ani = SIMON_ANI_JUMP_RIGHT;
			else ani = SIMON_ANI_JUMP_LEFT;
		}		
	}
	int alpha = 255;
	animations[ani]->Render(x - xcam, y - ycam, alpha);
	RenderBoundingBox(xcam, ycam);
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT: 
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP: 
		if (y>100) {
			vy = -SIMON_JUMP_SPEED_Y;
		}
		else vy = 0;
	case SIMON_STATE_IDLE: 
		vx = 0;
		level = 0;
		break;
	case SIMON_STATE_SIT_DOWN: //cài đặt việc ngồi cho Simon
		vx = 0;
		level = 1;
		break;
	case SIMON_STATE_ATTACK://cài đặt việc đánh cho Simon
		attacking = 1;
		attack_start += 100000;
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 
	right = x + SIMON_BIG_BBOX_WIDTH;
	bottom = y + SIMON_BIG_BBOX_HEIGHT;
}

