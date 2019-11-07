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
	int ny;
	int state;
	int currentAnimation;
	static int level;
	bool isCollision = false;
	int liveTime;
	std::string name;
	std::string idHiddenItem;
	std::string objectID;
	DWORD dt;
	static unordered_map<int, LPANIMATION> animations;

public:
	enum StateLive
	{
		STATE_DETROY = 1000,
		STATE_SHOW = 1001,
		STATE_EFFECT = 1002,
	};
	GameObject();
	static int getLevel() { return level; }
	void setLevel(int level) { this->level = level; }
	int getLiveTime() { return liveTime; }
	void setLiveTime(int liveTime) { this->liveTime = liveTime; }
	void SetPosition(D3DXVECTOR2 POS) { x = POS.x; y = POS.y; }
	D3DXVECTOR2 getPosition();
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void SetCurrentAni(int currentAni) { this->currentAnimation = currentAni; }
	int GetState() { return this->state; }
	int getID();
	void setID(int id) { this->id = id; }
	void setName(std::string name) { this->name = name; }
	std::string getName() { return name; }
	int getHeight();
	void setHeight(int height);
	int getWidth();
	void setWidth(int width);
	void setSpeed(float vx, float vy);
	std::string getIdHiddenItem();
	void setIdHiddenItem(std::string idHiddenItem);
	void setObjectID(std::string objectID) { this->objectID = objectID; }
	std::string getObjectID() { return objectID; }
	int getDirection() { return this->nx; }
	void setDirection(int nx) { this->nx = nx; }
	bool IsChangeLevel();
	bool checkCollision(RECT A, RECT B);
	bool IsCollision();
	bool setIscollision(bool isCollision);
	void RenderBoundingBox(Viewport* viewport);
	bool checkInsideViewPort(Viewport* viewport, D3DXVECTOR2 position);

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


