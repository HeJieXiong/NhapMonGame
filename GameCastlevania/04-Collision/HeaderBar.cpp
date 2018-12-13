#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "HeaderBar.h"

CHeaderBar::CHeaderBar(LPDIRECT3DDEVICE9 d3ddv)
{
	font1 = NULL;
	hr1 = D3DXCreateFont(d3ddv, 10, 7, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, L"(Arial)", &font1);
	SetRect(&fRectangle1, 0, 0, 400, 150);
}

void CHeaderBar::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	int ani;
	ani = HEADER_BAR_ANI;
	int alpha = 255;
	animations[ani]->Render(x-20, y-5, alpha);
}
void CHeaderBar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + HEADER_BAR_BBOX_WIDTH;
	bottom = y + HEADER_BAR_BBOX_HEIGHT;
}
void CHeaderBar::DrawHeaderbar() {
	score = "SCORE-";
	player = "PLAYER ";
	enemy = "ENEMY ";
	time = "TIME ";
	stage = "STAGE ";
	space = "                        ";
	string a= to_string(score_);
	string b = to_string(time_);
	string c = to_string(stage_);
	string d = to_string(heart_);
	string e = to_string(p_);
	score =score+a+ space +time+b+ space + stage+c + "\n"+player+"\n"+enemy;
	
	font1->DrawTextA(NULL, score.c_str(), -1, &fRectangle1, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}



