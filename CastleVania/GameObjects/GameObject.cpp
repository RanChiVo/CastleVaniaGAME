#include <d3dx9.h>

#include "../Debug/DebugOut.h"
#include "../Game.h"
#include "GameObject.h"
#include "../Animations/Animations.h"

vector<LPANIMATION> GameObject::animations;

void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = Animations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}

GameObject::GameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
}

void GameObject::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void GameObject::Render()
{
}

GameObject::~GameObject()
{
}
