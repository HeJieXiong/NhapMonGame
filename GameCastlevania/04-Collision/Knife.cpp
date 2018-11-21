#include "Knife.h"
#include "Textures.h"
#include "Sprites.h"
#include <chrono>
#include <thread>


CKnife::CKnife() {
	type_morningstar = 0;
}

CKnife::~CKnife() {

}

CKnife * CKnife::_instance = NULL;

CKnife *CKnife::GetInstance()
{
	if (_instance == NULL) _instance = new CKnife();
	return _instance;
}

void CKnife::Update_colison(vector<LPGAMEOBJECT> *coObjects) {
	float top = y;
	float left = x;
	float bottom;
	float right;
	if (type_morningstar == 0) {
		top = y;
		left = x;
		bottom = y + KNIFE_BOX_HEIGHT;
		right = x + KNIFE_BOX_WIDTH;
	}
	if (type_morningstar == 1) {
		top = y;
		left = x;
		bottom = y + KNIFE_BOX_HEIGHT;
		right = x + KNIFE_BOX_WIDTH;
	}
	if (GetTickCount() - attack_start > KNIFE_ATTACK_TIME) {
		attack_time += 1;
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
					coObjects->at(i)->y = 0;
				}
			}
		}
		attack_time = 0;
	}
}
void CKnife::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	
		top = y;
		left = x;
		bottom = y + KNIFE_BOX_HEIGHT;
		right = x + KNIFE_BOX_WIDTH;
	
	
	attack_time = 0;

}

void CKnife::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
		animations[0]->Render(50,50);
		//RenderBoundingBox_MoringStar(xcam, ycam);
		//if (state == 0) {//SIMON_ANI_SIT_ATTACK_LEFT
		//	x = x_simon - 25;
		//	y = y_simon + 15;
		//	int ani = 0;

		//	animations[ani]->Render(x - xcam - 2, y - ycam - 10);
		//	//RenderBoundingBox_MoringStar(x, y);
		//	RenderBoundingBox_MoringStar(xcam, ycam);
		//}
		//if (state == 1) {//SIMON_ANI_SIT_ATTACK_RIGHT
		//	x = x_simon;
		//	y = y_simon + 15;
		//	int ani = 0;
		//	animations[ani]->Render(x - xcam - 15, y - ycam - 10);
		//	//RenderBoundingBox_MoringStar(x, y);
		//	RenderBoundingBox_MoringStar(xcam, ycam);
		//}
		//if (state == 2) {//SIMON_ANI_ATTACK_LEFT
		//	int ani = 0;
		//	x = x_simon - 26;
		//	y = y_simon + 10;
		//	animations[ani]->Render(x - xcam - 4, y - ycam - 10);
		//	//RenderBoundingBox_MoringStar(x, y);
		//	RenderBoundingBox_MoringStar(xcam, ycam);
		//}
		//if (state == 3) {//SIMON_ANI_ATTACK_RIGHT
		//	x = x_simon;
		//	y = y_simon + 10;
		//	int ani = 0;
		//	animations[ani]->Render(x - xcam - 15, y - ycam - 10);
		//	RenderBoundingBox_MoringStar(xcam, ycam);
		//}
	
}


