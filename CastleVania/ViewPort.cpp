#include "Viewport.h"

constexpr float VIEWPORT_SPEED_X = 0.0406f;

Viewport::Viewport(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	startViewportX = 0;
	endViewportX = 0;
	startViewportY = 0;
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

void Viewport::autoMove(DWORD dt)
{
	x += VIEWPORT_SPEED_X * dt;
}

float Viewport::getStartViewportX()
{
	return startViewportX;
}

void Viewport::setEndViewPortX(float endViewport)
{
	this->endViewportX = endViewport;
}

float Viewport::getEndViewportX()
{
	return endViewportX;
}

void Viewport::setStartViewPortY(float startViewportY)
{
	this->startViewportY = startViewportY;
}

float Viewport::getStartViewportY()
{
	return startViewportY;
}

void Viewport::setStartViewPortX(float startViewport)
{
	this->startViewportX = startViewport;
}

Viewport::~Viewport()
{
}
