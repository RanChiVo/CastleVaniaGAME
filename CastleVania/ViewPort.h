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

	ViewPort();

	D3DXVECTOR2  WorldToScreen(D3DXVECTOR2 Object);

	D3DXVECTOR2  ScreenToWorld(D3DXVECTOR2 Object);

	~ViewPort();
};

