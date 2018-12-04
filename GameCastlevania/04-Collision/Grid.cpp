#include "Grid.h"

CGrid::CGrid(int id, float & x, float & y, float & screen_width, float & screen_height)
{
	this->id = id;
	this->width = screen_width;
	this->height = screen_height;
}

void CGrid::AddGrid(LPGAMEOBJECT obj)
{
	objects.push_back(obj);
}

void CGrid::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void CGrids::Add(int id, LPCGrid tex)
{
	grids[id] = tex;
}

LPCGrid CGrids::GetGrid(int id)
{
	return LPCGrid();
}
