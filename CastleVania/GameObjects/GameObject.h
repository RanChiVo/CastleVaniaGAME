#pragma once
#include <vector>
#include "../Textures/Textures.h"
#include "../SpriteManagements/Sprites.h"
#include "../Animations/Animations.h"
#include "../Viewport.h"
#include "../Direct3DManager.h"

using namespace std;

class GameObject;
typedef GameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	float dx, dy;		// *RELATIVE* movement distance between this object and obj
	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

class GameObject	
{
protected:
	EntityID id;
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
	int mainId;
	vector<D3DXVECTOR2> cellId;
	int currentAnimation;
	bool isCollision = false;
	bool isInSideActiveArea = false;
	DWORD liveTime;
	std::string name;
	std::string idHiddenItem;
	std::string objectID ;
	std::string nameEnemy;
	float startViewPort;
	float endViewPort;
	bool isTouched = false;
	DWORD dt;

	LPANIMATION_SET animation_set;

public:
	enum StateLive
	{
		STATE_DETROY = 1000,
		STATE_SHOW = 1001,
		STATE_HIDDEN = 1002,
		STATE_EFFECT = 1003,
	};
	GameObject();
	bool IsTouched(){ return isTouched; }
	bool IsInSideActiveArea() { return isInSideActiveArea; }
	void SetInSideActiveArea(bool isInside) { this->isInSideActiveArea = isInside; }
	void SetBeTouched(bool isTouchded) { this->isTouched = isTouchded; }
	void setMainId(int mainId) { this->mainId = mainId; }
	int getMainId() { return mainId; }
	void setCellId(std::string cellIdString);
	vector<D3DXVECTOR2> getCellId() { return cellId; }
	DWORD getLiveTime() { return liveTime; }
	void setLiveTime(DWORD liveTime) { this->liveTime = liveTime; }
	void SetPosition(D3DXVECTOR2 POS) { x = POS.x; y = POS.y; }
	D3DXVECTOR2 getPosition();
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void SetVx(float vx) { this->vx = vx; }
	void SetVy(float vy) { this->vy = vy; }

	float GetVx() { return vx; }
	float GetVy() { return vy; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void SetCurrentAni(int currentAni) { this->currentAnimation = currentAni; }
	int GetState() { return this->state; }
	EntityID getID();
	void setID(EntityID id) { this->id = id; }
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
	void setEnemyName(std::string nameEnemy) { this->nameEnemy = nameEnemy; }
	std::string getEnemyName() { return nameEnemy; }

	void set_nx(int nx) { this->nx = nx; }
	int get_nx() { return nx; }
	void set_ny(int ny) { this->ny = ny; }
	int get_ny() { return ny; }
	bool checkCollision(RECT A, RECT B);
	bool IsCollision();
	bool setIscollision(bool isCollision);
	void RenderBoundingBox(Viewport* viewport);
	bool checkInsideViewPort(Viewport* viewport);

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }
	LPANIMATION_SET GetAnimationSet() { return animation_set; }
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents,
		vector<LPCOLLISIONEVENT> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny,
		float &rdx,
		float &rdy);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Viewport* viewport) = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom)=0;
	virtual void SetState(int state) { this->state = state; }
	virtual ~GameObject();
};


