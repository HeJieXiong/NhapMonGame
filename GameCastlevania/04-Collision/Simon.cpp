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
	if (state != SIMON_STATE_ATTACK)isLastFrame = 0;
	// Simple fall down
	if (has_g == 1) {
		if (on_jump == 2) 
			vy += SIMON_SPEED_JUMP_DOWN*dt;

		else
		vy += SIMON_GRAVITY * dt;
	
		between_stair = 0;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	/*if ( GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}*/
	//if (state != SIMON_STATE_JUMP)on_jump = 0;

	if (on_jump == 1) {
		if (GetTickCount() - jump_start < SIMON_JUMP_TIME)
		{
			state = SIMON_STATE_JUMP;

			vy = -SIMON_STAY_JUMP_SPEED_Y;
		}
		if (jump_walk == 1) {
			vx = -SIMON_JUMP_SPEED_X;
		}
		if (jump_walk == 2) {
			vx = SIMON_JUMP_SPEED_X;
		}
		
		if (jump_walk == 0) {
			if (GetTickCount() - jump_start >= SIMON_JUMP_TIME && GetTickCount() - jump_start <= SIMON_JUMP_DOWN_TIME) {

				
				vy = -SIMON_STAY_JUMP_SPEED_Y;
				state = SIMON_STATE_JUMP;
			}
			if (GetTickCount() - jump_start > SIMON_JUMP_DOWN_TIME) {
				on_jump = 0;
				if (taking_jump == 0)
					state = SIMON_STATE_IDLE;
				else {

					state = SIMON_STATE_EXTRA;
				}
			}
		}
		else {
			if (GetTickCount() - jump_start >= SIMON_JUMP_TIME && GetTickCount() - jump_start <= SIMON_JUMP_DOWN_TIME) {

				if (jump_walk == 1) {
					vx = -SIMON_JUMP_SPEED_X;
					vy = SIMON_JUMP_SPEED_Y;
				}
				else
					vx = SIMON_JUMP_SPEED_X;
					vy = SIMON_JUMP_SPEED_Y;
				
			}
		}
		if (GetTickCount() - jump_start > SIMON_JUMP_DOWN_TIME) {
			on_jump = 2;
			jump_walk = 0;
			jump_start = 0;
			vx = 0;
			vy = 0;
			if (taking_jump == 0)
				state = SIMON_STATE_IDLE;
			else {

				state = SIMON_STATE_EXTRA;
			}
		}

	}
	
	if (attacking == 1) {
		if (GetTickCount() - attack_start < SIMON_ATTACK_TIME)
		{
			state = SIMON_STATE_ATTACK;
			vx = 0;
			
			if ( GetTickCount() - attack_start > 300 )
				isLastFrame = 1;
			attack_time += dt;
			
		}
	}
	if (attack_time > dt * 25) {
		attacking = 0;
		attack_time = 0;
		if (attack_then_walk == 1) 
			state = SIMON_STATE_WALKING_LEFT;
		
		if (attack_then_walk == 2)
			state = SIMON_STATE_WALKING_RIGHT;
			attack_then_walk = 0;
		
	}
	if (is_walking == 1 && state == SIMON_STATE_DISAPPEAR) {
		if (GetTickCount() - walking_start > SIMON_WALKING_TIME)
		{
			state = SIMON_STATE_DISAPPEAR;
			walking_time += dt;
		}
	}
	if (walking_time > dt * 30) {
		y = -9999;
		walking_time = 0;
	}
	if (state==SIMON_STATE_EXTRA && on_jump==0) {
		vx = 0;
		if (GetTickCount() - take_item_start < SIMON_TAKING_TIME)
		{	
			state_extra = 1;
			
			taking_time += dt;
			state = SIMON_STATE_EXTRA;
		}
		if (taking_time > dt*25 ) {	
			state = SIMON_STATE_IDLE;
			taking_time = 0;
			state_extra = 0;
			take_item_start = 0;
			taking_jump = 0;
		}
		/*else {
			state = SIMON_STATE_IDLE;
			taking_time = 0;
			state_extra = 0;
			take_item_start = 0;
		}*/
	}
	if (coEvents.size() == 0)//new code
	{
		x += dx;
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{
				CBrick *brick = dynamic_cast<CBrick *>(e->obj);

				if (e->nx != 0 || e->ny < 0)
				{
					isFalling = 0;
					on_jump = 0;
					touch_stair_jump = 0;
				}
			}

			if (dynamic_cast<CItem *>(e->obj))
			{
				CItem *item = dynamic_cast<CItem *>(e->obj);

				if (e->nx != 0 || e->ny < 0)
				{
					item->check_taken = 1;
					item->y = -9850;
					item->vy = 0;
					item->dt = 0;
					point += 100;
					if (item->ani == 900) {
						morningstar->SetType(1);
						take_item_start = GetTickCount();
						if(on_jump==0)
						state = SIMON_STATE_EXTRA;
						else taking_jump = 1;
						
					}
					if (item->ani == 903) {
						has_wp = 1;
					}

				}
			}

			/*if (dynamic_cast<CGhost *>(e->obj))
			{
				CGhost *ghost = dynamic_cast<CGhost *>(e->obj);

				if (e->nx != 0 || e->ny <0)
				{
					vx=-100;
				}
			}*/
			if (dynamic_cast<CStair *>(e->obj))
			{
				CStair *stair = dynamic_cast<CStair *>(e->obj);
				isFalling = 0;
				if (e->nx != 0 || e->ny < 0 || e->ny>0)
				{
					
					state_direction_on_stair = stair->stair_direction;
					if (is_on_stair == 0 && (stair->type_stair == 1 || stair->type_stair == 2) && stair->stair_direction != 0) {//Bật is_on_stair khi Simon vào chỗ cầu thang
						is_on_stair = 1;
						has_g = 1;
					}
					if (stair->type_stair == 2) {
						if (is_on_stair == 1 &&  has_g == 0) {
							has_g = 1;
							is_on_stair = 0;
							//x += dx;
							//y += dy;
						}
						if (on_jump == 1) {																						
								y += dy;
								touch_stair_jump = 1;
						}
						if(on_jump==0)touch_stair_jump = 0;
					}
					if (is_on_stair == 1 && stair->type_stair == 2 && has_g == 1) {
						is_on_stair = 1;
						//x += dx;
						//y += dy;
					}
					if (stair->type_stair == 3 && stair->stair_direction == 0) {
						has_g = 1;
						is_on_stair = 0;
					}
					if ((state_direction_on_stair == 1 || state_direction_on_stair == 3) && has_g == 0 && stair->type_stair == 1)// Simon khi đi xuống
					{
						has_g = 1;
					}
					if (stair->type_stair != 2) {
						on_jump = 0; 
						
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
	//DebugOut(L"vy %f\n", this->vy);
	//
	//	DebugOut(L"dang roi %d\n", this->isFalling);
	DebugOut(L"X %f\n", this->x);

	/*DebugOut(L"Dir %d\n", this->state_direction_on_stair);
	DebugOut(L"Between %d\n", this->between_stair);
	DebugOut(L"has_g %d\n", this->has_g);
	DebugOut(L"on_stair %d\n", this->is_on_stair);*/
	DebugOut(L"point %d\n", this->point);


}

void CSimon::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	int ani;
	if (state == SIMON_STATE_EXTRA ) {
		if (nx < 0) {
			ani = SIMON_ANI_STAY_EXTRA_LEFT;
		}
		else ani = SIMON_ANI_STAY_EXTRA_RIGHT;
			
	}
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	if (state == SIMON_STATE_SIT_DOWN) {
		if (nx < 0) {
			ani = SIMON_ANI_SIT_DOWN_LEFT;
		}
		else ani = SIMON_ANI_SIT_DOWN_RIGHT;
	}
	else if (state == SIMON_STATE_ATTACK) {
		
			
		morningstar->attack_start = GetTickCount();
		if (level == 1) {
			
			if (nx < 0) {
				ani = SIMON_ANI_SIT_ATTACK_LEFT;
				if (attack_wp == 0) {
					morningstar->attack_start = GetTickCount();
					morningstar->state = 0;
					morningstar->Render(xcam, ycam, x, y);

					isLastFrame = 0;
				}
				else if (attack_wp == 1) {
					knife->vx = -KNIFE_GRAVITY * dt;
					knife->attack_sit = 1;
					knife->AddAnimation(1101);
				}
			}
			else {
				ani = SIMON_ANI_SIT_ATTACK_RIGHT;
				if (attack_wp == 0) {
					morningstar->attack_start = GetTickCount();
					morningstar->state = 1;
					morningstar->Render(xcam, ycam, x, y);
				}
				else if (attack_wp == 1) {
					knife->vx = KNIFE_GRAVITY * dt;
					knife->attack_sit = 1;
					knife->AddAnimation(1100);
				}
			}
		}
		if (level == 0) {
			
			if (nx < 0) {
				if (is_on_stair == 1) {
					if (walking_up == 2) {
						ani = SIMON_ANI_ATTACK_LEFT_DOWN;
						morningstar->attack_on_stair = 2;
						
					}
					if (walking_up == 1) {
						ani = SIMON_ANI_ATTACK_LEFT_UP;
						morningstar->attack_on_stair = 1;
					}
					if (walking_up == 0) {
						ani = SIMON_ANI_ATTACK_LEFT;
						morningstar->attack_on_stair = 0;
					}
				}
				else {
					ani = SIMON_ANI_ATTACK_LEFT;
					morningstar->attack_on_stair = 0;
				}
				if (attack_wp == 0) {
					
					morningstar->attack_start = GetTickCount();
					morningstar->state = 2;
					morningstar->Render(xcam, ycam, x, y);
					if (isLastFrame == 1) {
						morningstar->isLastFrame = 1;						
					}
				}
				else if (attack_wp == 1 && knife->is_fly == 0) {
					knife->is_fly = 1;
					knife->vx = -KNIFE_GRAVITY * dt;
					knife->AddAnimation(1101);
				}
			}
			else {
				if (is_on_stair == 1) {
					if (walking_up == 2) {
						ani = SIMON_ANI_ATTACK_RIGHT_DOWN;
						morningstar->attack_on_stair = 2;
					}
					if (walking_up == 1) {
						ani = SIMON_ANI_ATTACK_RIGHT_UP;
						morningstar->attack_on_stair = 1;
					}
					if (walking_up == 0) {
						ani = SIMON_ANI_ATTACK_RIGHT;
						morningstar->attack_on_stair = 0;
					}
				}
				else {
					morningstar->attack_on_stair = 0;
					ani = SIMON_ANI_ATTACK_RIGHT;
				}
				if (attack_wp == 0) {
					morningstar->attack_start = GetTickCount();
					morningstar->state = 3;
					morningstar->Render(xcam, ycam, x, y);
				}
				else if (attack_wp == 1 && knife->is_fly==0) {
					knife->is_fly = 1;
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
		//đi lên đi xuống cầu thang trái
		if (state_direction_on_stair == 1 && between_stair == 0 )
			ani = SIMON_ANI_ON_STAIR_LEFT;
		if (state_direction_on_stair == 2 && between_stair == 0) {
			if(walking_up==1)
				ani = SIMON_ANI_ON_STAIR_LEFT;
			else ani = SIMON_ANI_ON_STAIR_LEFT;
		}
		if (state_direction_on_stair == 2 && between_stair == 1) {
			if (walking_up == 1)
				ani = SIMON_ANI_ON_STAIR_LEFT;
			else ani = SIMON_ANI_DOWN_STAIR_LEFT;
		}
		if (state_direction_on_stair == 1 && between_stair == 1) {
			if (walking_up == 1)
				ani = SIMON_ANI_ON_STAIR_LEFT;
			else
				ani = SIMON_ANI_DOWN_STAIR_LEFT;
		}

		//đi xuống cầu thang phải
		if (state_direction_on_stair == 3 && between_stair == 0) {
			if (walking_up == 1)
				ani = SIMON_ANI_ON_STAIR_RIGHT;
			else ani = SIMON_ANI_DOWN_STAIR_RIGHT;
		}
		if (state_direction_on_stair == 4 && between_stair == 0)
			ani = SIMON_ANI_STAY_STAIR_RIGHT_UP;
		if (state_direction_on_stair == 3 && between_stair == 2)
			if (walking_up == 1)
				ani = SIMON_ANI_ON_STAIR_RIGHT;
			else ani = SIMON_ANI_DOWN_STAIR_RIGHT;
		if (state_direction_on_stair == 4 && between_stair == 2) {
			if(walking_up==1)
				ani = SIMON_ANI_ON_STAIR_RIGHT;
			else ani = SIMON_ANI_DOWN_STAIR_RIGHT;
		}
			

		if (state_direction_on_stair == 0) {
			if (nx > 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
			else if (nx < 0) ani = SIMON_ANI_BIG_IDLE_LEFT;
			
		}
	}
	else {
		if (state_extra == 0) {
			if (vx == 0) {
				if (between_stair == 1 || between_stair == 2) {
					if (has_g == 0) {
						if (walking_up == 1) {
							if (state_direction_on_stair == 1 || state_direction_on_stair == 2)
								ani = SIMON_ANI_STAY_STAIR_LEFT_UP;
							else if (state_direction_on_stair == 3 || state_direction_on_stair == 4)
								ani = SIMON_ANI_STAY_STAIR_RIGHT_UP;
						}
						if (walking_up == 2) {
							if (state_direction_on_stair == 3 || state_direction_on_stair == 4)
								ani = SIMON_ANI_STAY_STAIR_RIGHT_DOWN;
							else ani = SIMON_ANI_STAY_STAIR_LEFT_DOWN;
						}
					}
					/*else {
						if (nx > 0) ani = SIMON_ANI_BIG_IDLE_LEFT;
						else if (nx < 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;

					}*/
				}
				else {
					if (on_jump == 0 && state_extra == 0) {
						if (nx > 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
						else if (nx < 0) ani = SIMON_ANI_BIG_IDLE_LEFT;
						walking_up = 0;
					}
					else {
						if (nx > 0) ani = SIMON_ANI_JUMP_RIGHT;
						else if (nx < 0) ani = SIMON_ANI_JUMP_LEFT;
					}
				}

			}
			else if (vx > 0) {
				if (on_jump == 0 && state_extra == 0) {

					ani = SIMON_ANI_BIG_WALKING_RIGHT;
				}
				else ani = SIMON_ANI_JUMP_RIGHT;
			}
			else {
				if (on_jump == 0 && state_extra == 0)
					ani = SIMON_ANI_BIG_WALKING_LEFT;
				else ani = SIMON_ANI_JUMP_LEFT;
			}
			if (vy < 0) {
				if (nx > 0) ani = SIMON_ANI_JUMP_RIGHT;
				else ani = SIMON_ANI_JUMP_LEFT;
			}
		}
	}
	int alpha = 255;
	animations[ani]->Render(x - xcam - 7, y - ycam, alpha);
	RenderBoundingBox(xcam, ycam);
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:

	{
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		attack_then_walk = 0;
		break;
	}
	case SIMON_STATE_WALKING_LEFT:
	{
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		attack_then_walk = 0;
		break;
	}
	case SIMON_STATE_JUMP:
		/*	if(!is_on_stair)
			{*/
			//if(has_g)
			//if(vy==0)
			//if(vy<0)
		if (isFalling != 1)
			/*if (y > 140)*/ {
			//isFalling = true;
			vy = -SIMON_JUMP_SPEED_Y;
			on_jump = 1;
			jump_start = GetTickCount();
			
		}
		//return;
		//else vy = 0;
	//}
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
		animations[SIMON_ANI_SIT_ATTACK_LEFT]->Reset();
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

	if (state_direction_on_stair == 1) {
		vx = +SIMON_GRAVITY_ON_STAIR_X * dt;
		has_g = 0;
		vy = -SIMON_GRAVITY_ON_STAIR_Y * dt;
	}
	if (state_direction_on_stair == 3) {
		vx = -SIMON_GRAVITY_ON_STAIR_X * dt;
		has_g = 0;
		vy = -SIMON_GRAVITY_ON_STAIR_Y * dt;
	}
	if (state_direction_on_stair == 4) {
		vx = -SIMON_GRAVITY_DOWN_STAIR_X * dt;
		has_g = 0;
		vy = -SIMON_GRAVITY_DOWN_STAIR_Y * dt;
	}
	if (state_direction_on_stair == 2) {
		vx = +SIMON_GRAVITY_DOWN_STAIR_X * dt;
		
		vy = -SIMON_GRAVITY_DOWN_STAIR_Y * dt;
		has_g = 0;
	}

}
void CSimon::Walking_down_stair()
{

	if (state_direction_on_stair == 4) {
		vx = SIMON_GRAVITY_DOWN_STAIR_X * dt;

		vy = SIMON_GRAVITY_DOWN_STAIR_Y * dt;
		has_g = 0;
	}
	if (state_direction_on_stair == 2) {
		vx = -SIMON_GRAVITY_DOWN_STAIR_X * dt;

		vy = SIMON_GRAVITY_DOWN_STAIR_Y * dt;
		has_g = 0;
	}
	if (state_direction_on_stair == 1) {
		vx = -SIMON_GRAVITY_DOWN_STAIR_X * dt;
		has_g = 0;
		vy = SIMON_GRAVITY_DOWN_STAIR_Y * dt;
		between_stair = 1;
	}
	if (state_direction_on_stair == 3) {
		vx = SIMON_GRAVITY_DOWN_STAIR_X * dt;

		vy = SIMON_GRAVITY_DOWN_STAIR_Y * dt;
		has_g = 0;
		between_stair = 2;
	}

	/*if (state_direction_on_stair == 1) {
		vx = +SIMON_GRAVITY_ON_STAIR_X * dt;
		has_g = 0;
		vy = -SIMON_GRAVITY_ON_STAIR_Y * dt;
	}*/
	//if (state_direction_on_stair == 3) {
	//	vx = -SIMON_GRAVITY_ON_STAIR_X * dt;
	//	has_g = 0;
	//	vy = -SIMON_GRAVITY_ON_STAIR_Y * dt;
	//}

}


