#include <d3dx9.h>
#include <algorithm>
#include "../DebugOut/DebugOut.h"
#include "../Game.h"
#include "GameObject.h"
#include "../Animations/Animations.h"
#include "../Viewport.h"
#include "../Direct3DManager.h"
#include "../Textures/Textures.h"

unordered_map<int, LPANIMATION> GameObject::animations;
int GameObject::level = 0;

int GameObject::getID()	
{
	return id;
}

int GameObject::getHeight()
{
	return this->height;
}

void GameObject::setHeight(int height)
{
	this->height = height;
}

int GameObject::getWidth()
{
	return this->width;
}

int GameObject::getDirection()
{
	return nx;
}

void GameObject::setWidth(int width)
{
	this->width = width;
}

std::string GameObject::getIdHiddenItem()
{
	return idHiddenItem;
}

void GameObject::setIdHiddenItem(std::string idHiddenItem)
{
	this->idHiddenItem = idHiddenItem;
}

bool GameObject::IsChangeLevel()
{
	return level;
}

void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = Animations::GetInstance()->Get(aniId);
	if (animations.count(aniId) > 0)
	{
		return;
	}
	animations.insert(make_pair(aniId, ani));
}

void GameObject::DeleteAnimation(int aniId)
{
	animations.erase(aniId);
}

D3DXVECTOR2 GameObject::getPosition()
{
	return D3DXVECTOR2(x, y);
}

void GameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

GameObject::GameObject()
{
	state = STATE_SHOW;
	x = y = 0;
	vx = vy = 0;
	nx = 1;
}

void GameObject::RenderBoundingBox(Viewport* viewport)
{
	Sprite *sprite;
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	sprite = new Sprite("BoundingBox", RECT{ rect.left, rect.top, rect.right, rect.bottom }, bbox);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	
	sprite->Draw(pos, 100);
}

bool GameObject::checkCollision(RECT A, RECT B)
{
	float left = B.left - A.right;
	float top = B.bottom - A.top;
	float right = B.right - A.left;
	float bottom = B.top - A.bottom;

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

bool GameObject::IsCollision()
{	
	return isCollision;
}

bool GameObject::setIscollision(bool isCollision)
{
	return isCollision;
}

LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	Game::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

void GameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void GameObject::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float & min_tx, float & min_ty,
	float & nx, float & ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

GameObject::~GameObject()
{
}
