#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"
#include "Morningstar.h"
#include "Fire.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	if (is_on_stair == 0)
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
			vx = 0;
			attack_time += dt;
		}
	}
	if (attack_time > dt * 25) {
		attacking = 0;
		attack_time = 0;
	}
	if (is_walking == 1 &&state== SIMON_STATE_DISAPPEAR) {
		if (GetTickCount() - walking_start >SIMON_WALKING_TIME)
		{
			state = SIMON_STATE_DISAPPEAR;
			walking_time += dt;
		}
	}
	if (walking_time > dt * 30) {
		y = -9999;
		walking_time = 0;
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
		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CItem *>(e->obj))
			{
				CItem *item = dynamic_cast<CItem *>(e->obj);

				if (e->nx != 0|| e->ny <0)
				{		
						item->check_taken = 1;
						item->y = -9850;
						item->vy = 0;
						item->dt = 0;
						test_val = item->ani;
						if (item->ani == 900) {
							morningstar->SetType(1);
						}
						if (item->ani == 903) {
							has_wp = 1;
						}
						
				}
			}
			if (dynamic_cast<CStair *>(e->obj))
			{
				CStair *stair = dynamic_cast<CStair *>(e->obj);

				if (e->nx != 0 || e->ny <0)
				{
					if (is_on_stair == 0&& stair ->type_stair==1) {
						is_on_stair = 1;
					}
					if (is_on_stair == 1&& stair->type_stair == 2) {
						vy += SIMON_GRAVITY * dt;
						vx += SIMON_GRAVITY * dt;
						is_on_stair = 0;
					}
				}
			}
		}
	}
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];	
	
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
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
						if (attack_wp == 0) {
							morningstar->state = 0;
							morningstar->Render(xcam, ycam, x, y);
						}
						else if (attack_wp == 1) {
							knife->vx = -KNIFE_GRAVITY * dt;
							knife->AddAnimation(1101);
						}
					}
					else {
						ani = SIMON_ANI_SIT_ATTACK_RIGHT;
						if (attack_wp == 0) {
							morningstar->state = 1;
							morningstar->Render(xcam, ycam, x, y);
						}
						else if (attack_wp == 1) {
							knife->vx = KNIFE_GRAVITY * dt;
							knife->AddAnimation(1100);
						}
					}
				}
				if (level == 0) {
					if (nx < 0) {
						ani = SIMON_ANI_ATTACK_LEFT;
						if (attack_wp == 0) {
							morningstar->state = 2;
							morningstar->Render(xcam, ycam, x, y);
						}
						else if (attack_wp == 1) {
							knife->vx = -KNIFE_GRAVITY * dt;
							knife->AddAnimation(1101);
						}
					}
					else {
						ani = SIMON_ANI_ATTACK_RIGHT;
						if (attack_wp == 0) {
							morningstar->state = 3;
							morningstar->Render(xcam, ycam, x, y);
						}
						else if (attack_wp == 1) {
							knife->vx = KNIFE_GRAVITY * dt;
							knife->AddAnimation(1100);						
						}
					}
				}	
	}
	else if (state == SIMON_STATE_DISAPPEAR) {
		ani = SIMON_ANI_DISAPPEAR;
	}
	else if (state == SIMON_STATE_ON_STAIR) {
		if (nx > 0)
			ani = SIMON_ANI_ON_STAIR_RIGHT;
		else ani = SIMON_ANI_ON_STAIR_LEFT;
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
	animations[ani]->Render(x - xcam-2.5, y - ycam, alpha);
	//RenderBoundingBox(xcam, ycam);
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
		if (y>140) {
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



void CSimon::Attack(CMorningstar *monringstar, float &x_cam, float &y_cam) {
	if (!attacking) {
		attacking = 1;
		animations[SIMON_ANI_ATTACK_RIGHT]->Reset();
		animations[SIMON_ANI_ATTACK_LEFT]->Reset();
		animations[SIMON_ANI_SIT_ATTACK_RIGHT]->Reset();
		animations[SIMON_ANI_SIT_ATTACK_LEFT ]->Reset();
		morningstar->animations[MORNINGSTAR_NORMAL_LEFT]->Reset();
		morningstar->animations[MORNINGSTAR_NORMAL_RIGHT]->Reset();
		morningstar->animations[MORNINGSTAR_TYPE_1_LEFT]->Reset();
		morningstar->animations[MORNINGSTAR_TYPE_1_RIGHT]->Reset();
	}
	
}

void CSimon::Attack_Weapons()
{
	
	if (!attacking) {
		attacking = 1;
		animations[SIMON_ANI_ATTACK_RIGHT]->Reset();
		animations[SIMON_ANI_ATTACK_LEFT]->Reset();
		animations[SIMON_ANI_SIT_ATTACK_RIGHT]->Reset();
		animations[SIMON_ANI_SIT_ATTACK_LEFT]->Reset();
		knife = new CKnife();
		
		objects_weapons.push_back(knife);
		combine_array = 1;
	}
	
}

void CSimon::Walking_on_stair()
{
	vy -= SIMON_GRAVITY_ON_STAIR * dt;
	vx += SIMON_GRAVITY_ON_STAIR *dt;
	x += dx;
}


