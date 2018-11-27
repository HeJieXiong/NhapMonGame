#include "Stage.h"

void CStage::SetStage(float x, float y)
{
	switch (stage)
	{
	case 1:
		map->level = 2;
	default:
		break;
	}
	map->DrawMap(x, y);
}
