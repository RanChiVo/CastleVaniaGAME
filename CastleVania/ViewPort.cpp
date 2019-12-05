#include "Viewport.h"

constexpr float VIEWPORT_SPEED_X = 0.07f;

Viewport::Viewport(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	state = STATE_ACTION;
}

D3DXVECTOR2 Viewport::WorldToScreen(D3DXVECTOR2 Object)
{
	return D3DXVECTOR2(Object.x - x, Object.y - y);
}

D3DXVECTOR2 Viewport::ScreenToWorld(D3DXVECTOR2 Object)
{
	return D3DXVECTOR2(Object.x + x, Object.y + y);
}

void Viewport::moveRight(DWORD dt)
{
	x += VIEWPORT_SPEED_X * dt;
}

Viewport::~Viewport()
{
}
