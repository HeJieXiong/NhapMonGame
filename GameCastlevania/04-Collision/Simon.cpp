#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"
#include "Morningstar.h"
#include "Fire.h"


void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	count = vy;
	if (state != SIMON_STATE_ATTACK)isLastFrame = 0;
	if (has_g == 1) {
		if (on_jump == 2)
			vy += SIMON_SPEED_JUMP_DOWN * dt;
		else
			vy += SIMON_GRAVITY * dt;

		between_stair = 0;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (jump_walk == 2 && can_jump == 0) {
		state = SIMON_STATE_WALKING_RIGHT;
	}
	if (on_jump == 1) {
		if (GetTickCount() - jump_start < SIMON_JUMP_TIME)
		{
			state = SIMON_STATE_JUMP;
			vy = -SIMON_STAY_JUMP_SPEED_Y;
		}
		if (jump_walk == 1 && can_jump == 1) {
			vx = -SIMON_JUMP_SPEED_X;
			vy = -SIMON_STAY_JUMP_WALK_SPEED_Y;
		}
		if (jump_walk == 2 && can_jump == 1) {
			vx = SIMON_JUMP_SPEED_X;
			vy = -SIMON_STAY_JUMP_WALK_SPEED_Y;
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
			if (GetTickCount() - jump_start > SIMON_JUMP_DOWN_TIME) {
				if (jump_walk == 0) {
					on_jump = 2;
					jump_walk = 0;
					jump_start = 0;
					vx = 0;
					vy = 0;
				}
				if (taking_jump == 0)
					state = SIMON_STATE_IDLE;
				else {
					state = SIMON_STATE_EXTRA;
				}
			}
		}
		else {
			if (GetTickCount() - jump_start >= SIMON_JUMP_WALK_TIME && GetTickCount() - jump_start <= SIMON_JUMP_WALK_DOWN_TIME) {
				if (jump_walk == 1) {
					vx = -SIMON_JUMP_SPEED_X;
					vy = SIMON_STAY_JUMP_WALK_SPEED_Y;
				}
				if (jump_walk == 2) {
					vx = SIMON_JUMP_SPEED_X;
					vy = SIMON_STAY_JUMP_WALK_SPEED_Y;
				}
			}
			if (GetTickCount() - jump_start > SIMON_JUMP_WALK_DOWN_TIME) {
				if (jump_walk != 0) {
					can_jump = 0;
					vy = SIMON_STAY_JUMP_WALK_SPEED_Y;
					jump_walk = 0;
					jump_start = 0;
					on_jump = 0;
				}
				if (taking_jump == 0)
					state = SIMON_STATE_IDLE;
				else {

					state = SIMON_STATE_EXTRA;
				}
			}
		}
	}
	if (attacking == 1) {
		if (GetTickCount() - attack_start < SIMON_ATTACK_TIME)
		{
			state = SIMON_STATE_ATTACK;
			vx = 0;

			if (GetTickCount() - attack_start > 300)
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
	if (state == SIMON_STATE_EXTRA && on_jump == 0) {
		vx = 0;
		if (GetTickCount() - take_item_start < SIMON_TAKING_TIME)
		{
			state_extra = 1;
			taking_time += dt;
			state = SIMON_STATE_EXTRA;
		}
		if (taking_time > dt * 25) {
			state = SIMON_STATE_IDLE;
			taking_time = 0;
			state_extra = 0;
			take_item_start = 0;
			taking_jump = 0;
		}
	}

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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{
				CBrick *brick = dynamic_cast<CBrick *>(e->obj);
				if (e->nx != 0 || e->ny < 0)
				{
					if (on_jump != 0) {
						state = SIMON_STATE_IDLE;
					}
					on_jump = 0;
					isFalling = 0;
					touch_stair_jump = 0;
					jump_start = 0;
					if (jump_walk != 0) {
						can_jump = 0;
					}
					jump_walk = 0;
					if (brick->type == 15 && wanna_go_down != 0 && has_g == 0 ) {
						y += dy;
					}
				}
			}
			else if (dynamic_cast<CItem *>(e->obj))
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
						if (on_jump == 0)
							state = SIMON_STATE_EXTRA;
						else taking_jump = 1;

					}
					if (item->ani == 903) {
						has_wp = 1;
					}

				}
			}
			else if (dynamic_cast<CGhost *>(e->obj))
			{
				CGhost *ghost = dynamic_cast<CGhost *>(e->obj);

				if (e->nx < 0|| e->nx >0 || e->ny < 0 || e->ny>0)
				{
					if (untouchable == 0) {
						start_heart = GetTickCount();
						is_heart = 1;
						state =SIMON_STATE_HEART;

					}
					else {
						ghost->x += dx;

					}
				}
			}
			else if (dynamic_cast<CStair *>(e->obj))
			{
				CStair *stair = dynamic_cast<CStair *>(e->obj);
				isFalling = 0;
				if (stair->stair_direction != 25) {
					state_direction_on_stair = stair->stair_direction;
				}
				if (e->nx < 0 || e->nx > 0 || e->ny < 0 || e->ny>0)
				{
					if (stair->type_stair == 15) {
						is_touch_change_stage_stair = 1;
						next_stage = 4;
					}
					if (stair->type_stair == 40) {
						is_touch_change_stage_stair = 1;
						next_stage = 5;
					}
					if (stair->type_stair == 35) {
						is_touch_change_stage_stair = 1;
						go_back_stage = 1;
						next_stage = 3;
					}
					if (stair->type_stair == 30) {
						is_touch_change_stage_stair = 1;
						go_back_stage = 2;
						next_stage = 3;
					}
					if (is_touch_center_stair == 1 && between_stair != 0) {
						is_touch_center_stair = 0;
					}
					if (on_jump != 0 || e->ny < 0 || e->ny>0)
					{
						if (stair->type_stair == 25 && on_jump == 0) {
							if (wanna_go_down == 0) {					
								y -= PUSH_UP_STAIR;
							}
							if (wanna_go_down == 1) {
								y += PUSH_UP_STAIR;
							}
						}
						if (stair->type_stair != 25 && on_jump==0) {
							y += PUSH_UP_STAIR;
						}
					}
					if (nx > 0) {
						x += dx;
					}
					if (nx < 0) {
						x += dx;
					}
					if (on_jump != 0) {
						on_jump = 0;
						state = SIMON_STATE_IDLE;
					}
					if (stair->type_stair == 1) {
						go_up = 1;
						go_down = 0;
						stair_center = stair->center;
					}
					if (stair->type_stair == 2) {
						go_down = 1;
						if (stair->special_stair == 0) {
							go_up = 0;
						}
						if (stair->special_stair == 1) {
							go_up = 1;
						}
					}
					if ((is_on_stair == 0 || is_on_stair == 1) && (stair->type_stair == 1 || stair->type_stair == 2 || stair->type_stair == 4) && stair->stair_direction != 0) {

						if (stair->type_stair == 1) {
							stair_center = stair->center;
						}
						if (stair->type_stair == 2 || stair->type_stair == 4) {
							if (stair->special_stair == 1) {
								is_touch_special_stair = 1;
								//stair_center = stair->center;
								stair_tail = stair->center;
								stair_head = stair->head;
							}
							if (stair->special_stair == 0) {
								stair_center = 100;
							}
						}
						if (x - stair->center <= 2 && x - stair->center >= -2) {
							is_touch_center_stair = 1;
						}
						is_on_stair = 1;
						has_g = 1;
					}
					if (stair->type_stair == 5) {
						if (is_on_stair != 0 && state != SIMON_STATE_WALKING_LEFT && state != SIMON_STATE_WALKING_RIGHT) {
							y += dy;
							state_direction_on_stair = 4;
							between_stair = 1;
							ani = SIMON_ANI_STAY_STAIR_RIGHT_DOWN;
						}
						else {
							is_on_stair = 0;
							state = SIMON_STATE_IDLE;
						}
					}
					if (stair->type_stair == 2) {
						if (is_on_stair == 1 && has_g == 0) {
							has_g = 1;
							is_on_stair = 0;
						}
						if (is_on_stair == 0) is_on_stair = 1;
						if (on_jump == 1) {
							y += dy;
							touch_stair_jump = 1;
						}
						if (on_jump == 0) touch_stair_jump = 0;
					}
					if (is_on_stair == 1 && stair->type_stair == 2 && has_g == 1) {
						is_on_stair = 1;
					}
					if (stair->type_stair == 3) {
						has_g = 1;
						is_on_stair = 0;
						stair_center = -99999;
						is_touch_special_stair = 0;
						wanna_go_up = 0;
						wanna_go_down = 0;
						//stair_head = -99999;
						//stair_tail = -99999;
					}
					if ((state_direction_on_stair == 1 || state_direction_on_stair == 3) && has_g == 0 && stair->type_stair == 1)
					{
						has_g = 1;
					}
					if (stair->type_stair != 2) {
						on_jump = 0;
					}
					if (stair->type_stair == 10) {
						touch_wake = 1;
					}
					if (stair->type_stair == 20) {
						touch_wake = 2;
					}
					if (stair->type_stair == 300) {
						touch_wake = 3;
					}
					if (stair->type_stair == 100) {
						is_touch_change_stage_stair = 1;
						stair_center = stair->x;
						stair_tail = stair->tail;
					}
					if (stair->type_stair == 200) {
						next_stage = 3;
					}
					if (stair->type_stair == 2 && stair->special_stair == 0) {
						wanna_go_up = 0;
						stair_center = stair->x;
					}
					if (stair->type_stair == 2 && stair->special_stair == 0) {
						wanna_go_up = 0;
						if (stair->stair_direction == 2) {
							stair_center = stair->x;
							stair_tail = -99999;
							stair_head = -99999;
						}
						if (stair->stair_direction == 4) {
							stair_center = stair->tail;
							stair_tail = -99999;
							stair_head = -99999;
						}
					}
					if (jump_walk != 0) {
						y -= PUSH_UP_STAIR_SPECIAL;
						jump_walk = 0;
						jump_start = 0;
						on_jump=0;
						can_jump = 0;
					}
				}
			}
		}
	}
	if (wanna_go_up == 1 && stair_tail != -99999) {
		stair_center = stair_tail;
	}
	if (wanna_go_up == 2 && stair_head != -99999) {
		stair_center = stair_head;
	}
	if (is_heart == 1) {
		if (GetTickCount() - start_heart <= SIMON_HEART_JUMP_TIME) {
			is_heart = 1;
			untouchable = 1;
			if (between_stair == 0) {
				vy = -SIMON_STAY_JUMP_HEART_Y;
				if (nx < 0)
					vx = SIMON_STAY_JUMP_HEART_X;
				if (nx > 0)
					vx = -SIMON_STAY_JUMP_HEART_X;
				x += vx * dt;
				state = SIMON_STATE_HEART;
			}
			if (between_stair != 0) {
				state = SIMON_STATE_EFFECT_ON_STAIR_LEFT;
			}
		}
		if (GetTickCount() - start_heart >= SIMON_HEART_JUMP_TIME && GetTickCount() - start_heart <= SIMON_HEART_TIME) {
			untouchable = 1;
			vx = 0;
			is_heart = 1;
			state = SIMON_STATE_IDLE;
		}
		if (GetTickCount() - start_heart > SIMON_HEART_TIME) {
			start_heart = 0;
			untouchable = 0;
			is_heart = 0;
			state = SIMON_STATE_IDLE;
		}
	}
	if (state == SIMON_STATE_HEART || state == SIMON_STATE_EFFECT_ON_STAIR_LEFT || state == SIMON_STATE_EFFECT_ON_STAIR_RIGHT) {
		check_state = 1;
	}
	else check_state = 2;
	if (walking_on == 1) {
		if (GetTickCount() - start_walking > 300) {
			walking_on = 0;
			start_walking = 0;
		}
	}
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CSimon::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	if (state == SIMON_STATE_EXTRA) {
		if (nx < 0) {
			ani = SIMON_ANI_STAY_EXTRA_LEFT;
		}
		else ani = SIMON_ANI_STAY_EXTRA_RIGHT;
	}
	else if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (state == SIMON_STATE_SIT_DOWN) {
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
				else if (attack_wp == 1 && knife->is_fly == 0) {
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
		if (state_direction_on_stair == 1 && between_stair == 0) {
			ani = SIMON_ANI_ON_STAIR_LEFT;
			nx = 1;
		}
		if (state_direction_on_stair == 2 && between_stair == 0) {
			if (walking_up == 1) {
				ani = SIMON_ANI_ON_STAIR_LEFT;
				nx = 1;
			}
			else ani = SIMON_ANI_DOWN_STAIR_LEFT;
		}
		if (state_direction_on_stair == 2 && between_stair == 1) {
			if (walking_up == 1) {
				nx = 1;
				ani = SIMON_ANI_ON_STAIR_LEFT;
			}
			else {
				ani = SIMON_ANI_DOWN_STAIR_LEFT;
			}
		}
		if (state_direction_on_stair == 1 && between_stair == 1) {

			if (walking_up == 1) {
				ani = SIMON_ANI_ON_STAIR_LEFT;
				nx = 1;
			}
			else {
				ani = SIMON_ANI_DOWN_STAIR_LEFT;
			}
		}
		if (state_direction_on_stair == 3 && between_stair == 0) {
			nx = -1;
			ani = SIMON_ANI_ON_STAIR_RIGHT;

		}
		/*if (state_direction_on_stair == 4 && between_stair == 0)
			ani = SIMON_ANI_STAY_STAIR_RIGHT_UP;*/
		if (state_direction_on_stair == 3 && between_stair == 2)
			if (walking_up == 1)
				ani = SIMON_ANI_ON_STAIR_RIGHT;
			else ani = SIMON_ANI_DOWN_STAIR_RIGHT;
		if (state_direction_on_stair == 4 && between_stair == 2) {
			if (walking_up == 1)
				ani = SIMON_ANI_ON_STAIR_RIGHT;
			else ani = SIMON_ANI_DOWN_STAIR_RIGHT;
		}
		if (state_direction_on_stair == 0) {
			if (nx > 0) ani = SIMON_ANI_BIG_IDLE_RIGHT;
			else if (nx < 0) ani = SIMON_ANI_BIG_IDLE_LEFT;
		}
	}
	else if (state == SIMON_STATE_HEART) {
		if (nx > 0)
			ani = SIMON_ANI_STAY_HEART_LEFT;
		if (nx < 0)
			ani = SIMON_ANI_STAY_HEART_RIGHT;
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
				}
				else {
					if (on_jump == 0 && state_extra == 0) {
						if (nx > 0) ani = SIMON_ANI_DOWN_STAIR_EFFECT_RIGHT;
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
	if (is_walking == 2) {
		walking_start = GetTickCount();
		is_walking = 3;
	}
	if (is_walking == 3) {

		if (GetTickCount() - walking_start < 2000) {
			vx = 0;
			is_walking = 3;
		}
		if (GetTickCount() - walking_start >= 2000 && GetTickCount() - walking_start <= 3000) {
			state = SIMON_STATE_WALKING_RIGHT;
			vx = SIMON_WALKING_SPEED;
			is_walking = 3;
		}
		if (GetTickCount() - walking_start > 3000) {
			next_stage = 3;
			is_walking = 0;
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
		if (isFalling != 1) {
			vy = -SIMON_JUMP_SPEED_Y;
			on_jump = 1;
			jump_start = GetTickCount();

		}
	case SIMON_STATE_IDLE:
		vx = 0;
		level = 0;
		break;
	case SIMON_STATE_SIT_DOWN:
		vx = 0;
		level = 1;
		break;
	case SIMON_STATE_ATTACK:
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
	if (state == SIMON_STATE_JUMP) {
		right = x + SIMON_JUMP_BBOX_WIDTH;
		bottom = y + SIMON_JUMP_BBOX_HEIGHT;
	}
	else {
		right = x + SIMON_BIG_BBOX_WIDTH;
		bottom = y + SIMON_BIG_BBOX_HEIGHT;
	}
	if (on_jump == 0) {
		right = x + SIMON_BIG_BBOX_WIDTH;
		bottom = y + SIMON_BIG_BBOX_HEIGHT;
	}
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
	if (is_touch_center_stair == 0 && stair_center != -99999) {
		do_walking();
	}
	if (is_touch_center_stair == 1) {
		stair_center = -99999;
		if (!walking_on) {
			walking_on = 1;
			start_walking = GetTickCount();
			animations[SIMON_ANI_ON_STAIR_LEFT]->Reset();
			animations[SIMON_ANI_ON_STAIR_RIGHT]->Reset();
		}
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
}
void CSimon::Walking_down_stair()
{
	if (is_touch_center_stair == 0 && stair_center != -99999) {
		do_walking();
		wanna_go_down = 1;
	}
	if (is_touch_center_stair == 1) {
		stair_center = -99999;
		if (!walking_on) {
			walking_on = 1;
			start_walking = GetTickCount();
			animations[SIMON_ANI_DOWN_STAIR_LEFT]->Reset();
			animations[SIMON_ANI_DOWN_STAIR_RIGHT]->Reset();
		}
		if (state_direction_on_stair == 4) {
			has_g = 0;
			vx = SIMON_GRAVITY_DOWN_STAIR_X * dt;
			vy = SIMON_GRAVITY_DOWN_STAIR_Y * dt;

		}
		if (state_direction_on_stair == 2) {
			has_g = 0;
			vx = -SIMON_GRAVITY_DOWN_STAIR_X * dt;
			vy = SIMON_GRAVITY_DOWN_STAIR_Y * dt;
		}
		if (state_direction_on_stair == 1) {
			has_g = 0;
			vx = -SIMON_GRAVITY_DOWN_STAIR_X * dt;
			vy = SIMON_GRAVITY_DOWN_STAIR_Y * dt;
			between_stair = 1;
		}
		if (state_direction_on_stair == 3) {
			has_g = 0;
			vx = SIMON_GRAVITY_DOWN_STAIR_X * dt;
			vy = SIMON_GRAVITY_DOWN_STAIR_Y * dt;
			between_stair = 2;
		}
	}
}
void CSimon::do_walking() {
	if (is_touch_center_stair == 0) {
		if (x - stair_center <= -1) {
			nx = 1;
			vx = SIMON_WALKING_SPEED;
			state = SIMON_STATE_WALKING_RIGHT;
		}
		if (x - stair_center >= 1) {
			nx = -1;
			vx = -SIMON_WALKING_SPEED;
			state = SIMON_STATE_WALKING_LEFT;
		}
		if (x - stair_center<2 && x - stair_center >-2) {
			is_touch_center_stair = 1;
		}
	}
}
void CSimon::do_change_stair() {
	if (next_stage == 1) {
		if (can_turn == 0) {
			if (x - stair_center >= 2) {
				nx = -1;
				vx = -SIMON_WALKING_SPEED;
				state = SIMON_STATE_WALKING_LEFT;
			}
		}
		if (x - stair_center<15 && x - stair_center >-15) {
			can_turn = 1;
			nx = 1;
			vx = SIMON_WALKING_SPEED;
			state = SIMON_STATE_WALKING_RIGHT;
		}
		if (x - stair_tail<1 && x - stair_tail >-1 && can_turn == 1) {
			is_touch_change_stage_stair = 0;
			next_stage = 2;
		}
	}
}
void CSimon::do_change_stair_2() {
	if (next_stage == 2) {
		nx = 1;
		vx = SIMON_WALKING_SPEED;
		state = SIMON_STATE_WALKING_RIGHT;
		open_door = 1;
	}
}

