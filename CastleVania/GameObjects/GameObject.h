#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <unordered_map>
#include "../Animations/Animation.h"
#include "../CollisionEvent.h"

using namespace std;

class CollisionEvent;


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

	int state;

	int currentAnimation;
	
	static unordered_map<int, LPANIMATION> animations;

public:
	GameObject();

	virtual void SetPosition(D3DXVECTOR2 POS) { x = POS.x; y = POS.y; }
	virtual void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	virtual void SetState(int state) { this->state = state; }
	virtual int GetState() { return this->state; }
	virtual int GetDirection() { return this->nx; }

	static void AddAnimation(int aniId);
	D3DXVECTOR2 getPosition();
	virtual void Update(DWORD dt);
	virtual void handleCollision();
	virtual void Render(Viewport* viewport);
	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;

	void RenderBoundingBox();
	//LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	/*void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);
*/
	virtual ~GameObject();
};

//typedef GameObject* LPGAMEOBJECT;
