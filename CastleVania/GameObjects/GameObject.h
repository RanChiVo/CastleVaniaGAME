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
	int id;
	float x;
	float y;
	int height;
	int width;
	float dx;	
	float dy;	
	float vx;
	float vy;
	int nx;
	int state;
	int currentAnimation;
	static int level;
	bool isCollision = false;
	int liveTime;

	std::string idHiddenItem;
	DWORD dt;
	static unordered_map<int, LPANIMATION> animations;

public:
	GameObject();
	static int getLevel() { return level; }
	void setLevel(int level) { this->level = level; }
	int getLiveTime() { return liveTime; }
	void setLiveTime(int liveTime) { this->liveTime = liveTime; }
	enum StateLive
	{
		STATE_DETROY = 1000,
		STATE_SHOW = 1001,
		STATE_FIRE = 1002,
	};
	virtual void SetPosition(D3DXVECTOR2 POS) { x = POS.x; y = POS.y; }
	virtual D3DXVECTOR2 getPosition();
	virtual void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	virtual void SetCurrentAni(int currentAni) { this->currentAnimation = currentAni; }
	virtual int GetState() { return this->state; }
	virtual int getID();
	virtual int getHeight();
	virtual void setHeight(int height);
	virtual int getWidth();
	virtual void setWidth(int width);
	virtual std::string getIdHiddenItem();
	virtual void setIdHiddenItem(std::string idHiddenItem);

	virtual int getDirection() { return this->nx; }
	virtual void setDirection(int nx) { this->nx = nx; }
	virtual bool IsChangeLevel();
	virtual bool checkCollision(RECT A, RECT B);
	virtual bool IsCollision();
	virtual bool setIscollision(bool isCollision);

	void RenderBoundingBox(Viewport* viewport);

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
	static void DeleteAnimation(int aniId);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Viewport* viewport) = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom)=0;
	virtual void SetState(int state) { this->state = state; }

	virtual ~GameObject();
};


