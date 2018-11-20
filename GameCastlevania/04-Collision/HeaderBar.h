#pragma once
#include "GameObject.h"
#include "Camera.h"
#define HEADER_BAR_STATE 100
#define HEADER_BAR_ANI 0
#define HEADER_BAR_BBOX_WIDTH  20
#define HEADER_BAR_BBOX_HEIGHT 20
class CHeaderBar : public CGameObject
{
private:
	ID3DXFont * font1;
	RECT fRectangle1;
	std::string score;
	std::string time;
	std::string stage;
	std::string heart;	
	std::string p;
	HRESULT hr1;
public:
	int score_=0;
	int time_ = 0;
	int stage_ = 1;
	int heart_ = 3;
	int p_ = 0;
	CHeaderBar(LPDIRECT3DDEVICE9 d3ddv);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void DrawHeaderbar(int &x,int &y, int &a, int  &b);
};
