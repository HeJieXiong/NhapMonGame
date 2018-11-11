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
	animations[ani]->Render(x, y, alpha);
}
void CHeaderBar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + HEADER_BAR_BBOX_WIDTH;
	bottom = y + HEADER_BAR_BBOX_HEIGHT;
}
void CHeaderBar::DrawHeaderbar() {
	message1 = "SCORE-00000\nPLAYER\nENEMY";
	font1->DrawTextA(NULL, message1.c_str(), -1, &fRectangle1, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}



