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

EntityID GameObject::getID()	
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

void GameObject::setWidth(int width)
{
	this->width = width;
}

void GameObject::setSpeed(float vx, float vy)
{
	this->vx = vx;
	this->vy = vy;
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

void GameObject::setCellId(std::string cellIdString)
{
	cellId.clear();
	while (!cellIdString.empty())
	{
		std::string temp = cellIdString.substr(0, cellIdString.find(" "));
		std::string x = temp.substr(0, temp.find(","));
		std::string y = temp.substr(temp.find(",") + 1, temp.length() - 1);
		cellId.push_back(D3DXVECTOR2(std::stoi(x), std::stoi(y)));
		if (cellIdString.find(" ") > cellIdString.size()) break; 
		else cellIdString.erase(0, cellIdString.find(" ") + 1);
	}
}

void GameObject::RenderBoundingBox(Viewport* viewport)
{
	Sprite *sprite;

	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->Get(ID_ENTITY_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	sprite = new Sprite("BoundingBox", RECT{ rect.left, rect.top, rect.right, rect.bottom }, bbox);

	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	if (id == ID_ENTITY_SIMON)
	{
		if (state == Simon::SIMON_STATE_SITDOWN ||
			state == Simon::SIMON_STATE_ATTACK_SITDOWN)
		{
			sprite->Draw(D3DXVECTOR2(pos.x + 20, pos.y + 20), 100);

		}
		else sprite->Draw(D3DXVECTOR2(pos.x + 20, pos.y), 100);
	}
	else sprite->Draw(pos, 100);
}

bool GameObject::checkInsideViewPort(Viewport * viewport)
{
	float l, t, r, b;
	GetBoundingBox(l, t, r, b);

	RECT viewportBB{ viewport->getX(), viewport->getY(),
		viewport->getX() + viewport->getWidth(), viewport->getY() + viewport->getHeight()};
	
	if ((checkCollision(viewportBB, RECT{ long(l), long(t), long(r), long(b) }))) return true;
	return false;
}

bool GameObject::checkCollision(RECT A, RECT B)
{
	return A.left < B.right && A.right > B.left && A.top < B.bottom && A.bottom > B.top;
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
