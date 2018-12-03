#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <unordered_map>
#include "../Animations/Animation.h"
#include "../Viewport.h"
#include "../EntityID.h"


using namespace std;

class GameObject;
typedef GameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }
	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class GameObject	
{
protected:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;
	DWORD dt;

	int state;
	int currentAnimation;
	D3DXVECTOR2 newpos = { 0, 0 };
	
	static unordered_map<int, LPANIMATION> animations;

	int id;
	int widthworld;
	bool isChangeLevel = false;

public:
		
	virtual void SetPosition(D3DXVECTOR2 POS) { x = POS.x; y = POS.y; }
	virtual void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	virtual void SetCurrentAni(int currentAni) { this->currentAnimation = currentAni; }
	virtual int GetState() { return this->state; }
	virtual int getID();
	virtual int GetDirection() { return this->nx; }
	virtual bool IsChangeLevel();
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void RenderBoundingBox(Viewport* viewport);
	void setNewposition(D3DXVECTOR2 pos);
	D3DXVECTOR2 getNewPos();
	void setWidthWorld(int widthWorld);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);
	static void AddAnimation(int aniId);
	D3DXVECTOR2 getPosition();
	GameObject();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Viewport* viewport) = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom)=0;
	virtual void SetState(int state) { this->state = state; }

	virtual ~GameObject();
};


