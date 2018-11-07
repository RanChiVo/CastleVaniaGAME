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
	
	static unordered_map<int, LPANIMATION> animations;

public:
	GameObject();

	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
	virtual void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	virtual void SetState(int state) { this->state = state; }
	virtual int GetState() { return this->state; }
	virtual int GetDierection() { return this->nx; }

	static void AddAnimation(int aniId);
		
	virtual void Update(DWORD dt);
	virtual void handleCollision();
	virtual void Render();
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
