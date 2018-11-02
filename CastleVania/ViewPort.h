#pragma once
#include <d3dx9.h>


class ViewPort
{
protected:

	float x;
	float y;
	float width;
	float height;

public:

	ViewPort(int x, int y, int width, int height);

	D3DXVECTOR2  WorldToScreen(D3DXVECTOR2 Object);

	D3DXVECTOR2  ScreenToWorld(D3DXVECTOR2 Object);

	D3DXVECTOR2	 GetPosition() { return D3DXVECTOR2(x, y); }

	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	
	float getWidth() { return width; }

	float getHeight() { return height; }

	~ViewPort();
};

