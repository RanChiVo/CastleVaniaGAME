#include "Viewport.h"

Viewport::Viewport(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

D3DXVECTOR2 Viewport::WorldToScreen(D3DXVECTOR2 Object)
{
	return D3DXVECTOR2(Object.x - x, Object.y - y);
}

D3DXVECTOR2 Viewport::ScreenToWorld(D3DXVECTOR2 Object)
{
	return D3DXVECTOR2(Object.x + x, Object.y + y);
}

Viewport::~Viewport()
{
}
