#include "ViewPort.h"



ViewPort::ViewPort()
{
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
