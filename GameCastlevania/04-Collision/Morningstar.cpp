#include "Morningstar.h"
#include "Textures.h"
#include "Sprites.h"
#include <chrono>
#include <thread>


CMorningstar::CMorningstar() {
//	type_morningstar = MORNINGSTAR_NORMAL;
}

CMorningstar::~CMorningstar() {
	
}

CMorningstar * CMorningstar::_instance = NULL;

CMorningstar *CMorningstar::GetInstance()
{
	if (_instance == NULL) _instance = new CMorningstar();
	return _instance;
}

void CMorningstar::Update_colison( vector<LPGAMEOBJECT> *coObjects) {
	float top = y;
	float left = x;
	float bottom = y + MORNINGSTAR_BOX_HEIGHT;
	float right = x + MORNINGSTAR_BOX_WIDTH;
	if (GetTickCount() - attack_start > MORNINGSTAR_ATTACK_TIME) {
		attack_time +=1;
	}
	if (attack_time > 15) {
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			coObjects->at(i);
			float top_co;
			float left_co;
			float bottom_co;
			float right_co;
			coObjects->at(i)->GetBoundingBox(left_co, top_co, right_co, bottom_co);
			if (bottom > top_co) {
				if ((right > left_co&&right < right_co) || (left > left_co&&left < right_co) || (left < left_co) && (right > right_co)) {
					coObjects->at(i)->SetState(100);
				}
			}
		}
		attack_time = 0;
	}
}
void CMorningstar::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	//if (GetTickCount() - attack_start > MORNINGSTAR_ATTACK_TIME) {
	//	attack_time += dt;
	//}
	//if(attack_time> 200*dt) {
		left = x;
		top = y;
		right = x + MORNINGSTAR_BOX_WIDTH;
		bottom = y + MORNINGSTAR_BOX_HEIGHT;
		attack_time = 0;
	//}
}

void CMorningstar::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	float check = 0;
	if (state == 0) {//SIMON_ANI_SIT_ATTACK_LEFT
		x = x_simon-25;
		y = y_simon+15;
		int ani = 0;
		
		animations[ani]->Render(x-xcam-2, y-ycam-10);
		//RenderBoundingBox_MoringStar(x, y);
		RenderBoundingBox_MoringStar(xcam, ycam);
	}
	if (state == 1) {//SIMON_ANI_SIT_ATTACK_RIGHT
		x = x_simon;
		y = y_simon+15;
		int ani = 1;
		animations[ani]->Render(x - xcam-15, y-ycam-10);
		//RenderBoundingBox_MoringStar(x, y);
		RenderBoundingBox_MoringStar(xcam,ycam);
	}
	if (state == 2) {//SIMON_ANI_ATTACK_LEFT
		int ani = 0;
		x = x_simon-26;
		y = y_simon+10;
		animations[ani]->Render(x - xcam-4, y-ycam-10 );
		//RenderBoundingBox_MoringStar(x, y);
		RenderBoundingBox_MoringStar(xcam, ycam);
	}
	if (state == 3) {//SIMON_ANI_ATTACK_RIGHT
		x = x_simon;
		y = y_simon+10;
		int ani = 1;
		animations[ani]->Render(x - xcam-15, y-ycam-10);
		//RenderBoundingBox_MoringStar(x, y);
		RenderBoundingBox_MoringStar(xcam, ycam);
	}
	
}

//void CMorningstar::LoadResource() {
//	CTextures * textures = CTextures::GetInstance();
//
//	CSprites * sprites = CSprites::GetInstance();
//	CAnimations * animations = CAnimations::GetInstance();
//	
//	LPANIMATION ani;
//	
//
//}


void CMorningstar::SetType(int type) {
	type_morningstar = type;
}