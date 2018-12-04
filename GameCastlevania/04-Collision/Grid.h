#pragma once
#include "GameObject.h"
class CGrid : public CGameObject {
public: 
	int id;
	float width;
	float height;
public:
	CGrid();
	vector<LPGAMEOBJECT>objects;
	CGrid(int id, float &x, float &y, float &screen_width, float &screen_height);
	void AddGrid(LPGAMEOBJECT obj);
	int GetId() { return id; };
	virtual void GetBoundingBox( float &left, float &top, float &right, float &bottom );
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	~CGrid();
};

typedef CGrid *LPCGrid;

class CGrids {
public:
	vector<LPCGrid> grids;
	CGrids();
	void Add(int id, LPCGrid tex);
	LPCGrid GetGrid(int id);
	~CGrids();
};