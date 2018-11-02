#include "ViewPort.h"

ViewPort::ViewPort(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

D3DXVECTOR2 ViewPort::WorldToScreen(D3DXVECTOR2 Object)
{
	return D3DXVECTOR2(Object.x - x, Object.y - y);
}

D3DXVECTOR2 ViewPort::ScreenToWorld(D3DXVECTOR2 Object)
{
	return D3DXVECTOR2(Object.x + x, Object.y + y);
}

ViewPort::~ViewPort()
{
}
