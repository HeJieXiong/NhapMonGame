#pragma once
#include "GameObject.h"
#include "Camera.h"
#define BACK_GROUND_STATE 100
#define BACK_GROUND_ANI 0
#define BACK_GROUND_BBOX_WIDTH  400
#define BACK_GROUND_BBOX_HEIGHT 600
class CBackGround : public CGameObject
{
public:

	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetCamera(Camera *camera);
private:
	Camera * mCamera;
};
