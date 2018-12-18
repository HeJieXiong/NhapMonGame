#include "Fish.h"

void CFish::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CFish::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	animations[1]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);
}

void CFish::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FISH_STATE_ATK_LEFT:
		vx = 0;
		isAttacking = true;
		break;
	case FISH_STATE_ATK_RIGHT:
		vx = 0;
		isAttacking = true;
		break;
	case FISH_STATE_JUMP_LEFT:
		vy = -FISH_JUMP_SPEED;
		nx = -1;
		break;
	case FISH_STATE_JUMP_RIGHT:
		vy = -FISH_JUMP_SPEED;
		nx = 1;
		break;
	case FISH_STATE_WALKING_LEFT:
		vx = -FISH_WALKING_SPEED;
		nx = -1;
		break;
	case FISH_STATE_WALKING_RIGHT:
		vx = FISH_WALKING_SPEED;
		nx = 1;
		break;
	case FISH_STATE_HIDE:
		vx = 0;
		vy = 0;
		hitWater = 0;
		break;
	}
}

void CFish::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + FISH_BBOX_WIDTH;
	bottom = y + FISH_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
}

void CBullet::Render()
{
	animations[0]->Render(x, y);
}

void CBullet::GetBoundingBox(float &left, float &top, float &right, float &bottom){
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;
}
