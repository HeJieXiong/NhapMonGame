#pragma once
#include <d3dx9.h>
#include <d3d9.h>

class Camera {
public:
	Camera(float width, float height);
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);

	float getWight();
	float getHeight();

	D3DXVECTOR3 GetPosition();
	RECT GetBound();

	~Camera();

private:
	int mWidth,mHeight;
	D3DXVECTOR3 mPosition;
};