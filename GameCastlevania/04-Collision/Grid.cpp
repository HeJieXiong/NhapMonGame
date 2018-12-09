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

void CGrid::Render(float & xcam, float & ycam, float & x_simon, float & y_simon)
{
}

void CGrids::Add(int id_grid, float x, float y, float scr_width, float scr_height)
{
	CGrid *grid = new  CGrid(id_grid,x,y,scr_width,scr_height);
	grids.push_back(grid);
}

LPCGrid CGrids::GetGrid(int id)
{
	return LPCGrid();
}
