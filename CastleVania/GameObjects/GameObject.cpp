#include <d3dx9.h>

#include "../DebugOut/DebugOut.h"
#include "../Game.h"
#include "GameObject.h"
#include "../Animations/Animations.h"
#include "../Viewport.h"

unordered_map<int, LPANIMATION> GameObject::animations;

void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = Animations::GetInstance()->Get(aniId);
	animations.insert(make_pair(aniId, ani));
}

D3DXVECTOR2 GameObject::getPosition()
{
	return D3DXVECTOR2(x, y);
}

GameObject::GameObject()
{
	dx = 0; 
	x = 0;
	y = 0;
	vx = vy = 0;
	nx = 1;
}

void GameObject::Update(DWORD dt)
{
	x += vx * dt;
	dx += vx * dt;
	y += vy * dt;
}

void GameObject::handleCollision()
{
}

void GameObject::Render(Viewport* viewport)
{
}

void GameObject::RenderBoundingBox()
{
}

//LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
//{
//	return LPCOLLISIONEVENT();
//}

//void GameObject::CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
//{
//}
//
//void GameObject::FilterCollision(vector<LPCOLLISIONEVENT>& coEvents, vector<LPCOLLISIONEVENT>& coEventsResult, float & min_tx, float & min_ty, float & nx, float & ny)
//{
//}

GameObject::~GameObject()
{
}
