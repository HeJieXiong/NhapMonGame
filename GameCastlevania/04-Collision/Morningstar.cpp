#include "Morningstar.h"
#include "Textures.h"
#include "Sprites.h"
#include <chrono>
#include <thread>


CMorningstar::CMorningstar() {
	type_morningstar = 0;
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
	float bottom ;
	float right ;
	if (type_morningstar == 0) {
		 top = y;
		 left = x;
		 bottom = y + MORNINGSTAR_BOX_HEIGHT;
		 right = x + MORNINGSTAR_BOX_WIDTH;
		
	}
	if (type_morningstar == 1) {
		 top = y;
		 left = x;
		 bottom = y + TYPE_1_BOX_HEIGHT;
		 right = x + TYPE_1_BOX_WIDTH;
		
	}
	if (GetTickCount() - attack_start > MORNINGSTAR_ATTACK_TIME && attacked==0) {
		attack_time += MORNINGSTAR_TIME_COUNT;
	}
	if (attack_time > MORNINGSTAR_TIME_CHECK && attacked==0) {
		for (INT i = 0; i < coObjects->size(); i++)
		{
			
				coObjects->at(i);
				float top_co;
				float left_co;
				float bottom_co;
				float right_co;
				coObjects->at(i)->GetBoundingBox(left_co, top_co, right_co, bottom_co);
				if (bottom > top_co) {
					if (((right > left_co&&right < right_co) || (left > left_co&&left < right_co)
						|| (left < left_co) && (right > right_co)) && ((top > top_co&& top < bottom_co)
							|| (bottom > top_co &&bottom < bottom_co))) {
						//coObjects->at(i)->SetState(200);
						coObjects->at(i)->y = -9850;
					}
				}
				if (coObjects->at(i)->y == -9850) {
					attacked = 1;
					attack_time = 0;
				}
		}
		
	}
}
void CMorningstar::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	if (type_morningstar == 0) {
		top = y;
		left = x;
		bottom = y + MORNINGSTAR_BOX_HEIGHT;
		right = x + MORNINGSTAR_BOX_WIDTH;
	}
	if (type_morningstar == 1) {
		top = y;
		left = x;
		bottom = y + TYPE_1_BOX_HEIGHT;
		right = x + TYPE_1_BOX_WIDTH;
	}
		attack_time = 0;

}

void CMorningstar::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	attacked = 0;
	if (type_morningstar == 0) {
		float check = 0;
		if (state == 0) {//SIMON_ANI_SIT_ATTACK_LEFT
			x = x_simon - 30;
			y = y_simon + 15;
			int ani = 0;

			animations[ani]->Render(x - xcam - 2, y - ycam - 10);
			//RenderBoundingBox_MoringStar(xcam, ycam);
		}
		if (state == 1) {//SIMON_ANI_SIT_ATTACK_RIGHT
			x = x_simon;
			y = y_simon + 15;
			int ani = 1;
			animations[ani]->Render(x - xcam - 15, y - ycam - 10);
			//RenderBoundingBox_MoringStar(xcam, ycam);
		}
		if (state == 2) {//SIMON_ANI_ATTACK_LEFT
			int ani = 0;
			x = x_simon - 30;
			y = y_simon + 10;
			animations[ani]->Render(x - xcam - 4, y - ycam - 10);
			//RenderBoundingBox_MoringStar(xcam, ycam);
		}
		if (state == 3) {//SIMON_ANI_ATTACK_RIGHT
			x = x_simon;
			y = y_simon + 10;
			int ani = 1;
			animations[ani]->Render(x - xcam - 15, y - ycam - 10);
			//RenderBoundingBox_MoringStar(xcam, ycam);
		}
	}
	if (type_morningstar == 1) {
		float check = 0;
		if (state == 0) {//SIMON_ANI_SIT_ATTACK_LEFT
			x = x_simon - 30;
			y = y_simon + 15;
			int ani = 2;

			animations[ani]->Render(x - xcam - 13, y - ycam-5 );
			//RenderBoundingBox_MoringStar(xcam, ycam);
		}
		if (state == 1) {//SIMON_ANI_SIT_ATTACK_RIGHT
			x = x_simon;
			y = y_simon + 15;
			int ani = 3;
			animations[ani]->Render(x - xcam - 16, y - ycam - 5);
			//RenderBoundingBox_MoringStar(xcam, ycam);
		}
		if (state == 2) {//SIMON_ANI_ATTACK_LEFT
			int ani = 2;
			x = x_simon - 30;
			y = y_simon + 10;
			animations[ani]->Render(x - xcam - 13, y - ycam - 5);
			//RenderBoundingBox_MoringStar(xcam, ycam);
		}
		if (state == 3) {//SIMON_ANI_ATTACK_RIGHT
			x = x_simon;
			y = y_simon + 10;
			int ani = 3;
			animations[ani]->Render(x - xcam - 16, y - ycam - 5);
			//RenderBoundingBox_MoringStar(xcam, ycam);
		}
		
	}

}


void CMorningstar::SetType(int a) {
	type_morningstar = a;
}