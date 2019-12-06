#pragma once
#include "../CastleVania/GameObjects/GameObject.h"
#include "../CastleVania/Enemy.h"
#include "../CastleVania/GameObjects/Floor.h"
#include "../CastleVania/GameObjects/Simon.h"
//https://strategywiki.org/wiki/Castlevania/Enemies


class Panther : public Enemy
{
private:
	Floor* floor = nullptr;
	Simon* simon = nullptr;
	bool isOnGround = false;
	bool activate = false;
	D3DXVECTOR4 bbPlayer;
	RECT bbActivateLeft;
	RECT bbActivateRight;

public:
	enum State {
		PANTHER_STATE_ACTIVATE,
		PANTHER_STATE_JUMP,
		PANTHER_STATE_IDLE,
	};
	Panther(D3DXVECTOR2 position, int nx);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void setActivate(bool isActivate) { this->activate = isActivate; }
	bool IsActivate() { return activate; }
	RECT getBBActivateLeft() { return bbActivateLeft; }
	void setBBActivateLeft(RECT bbActivateLeft);
	RECT getBBActivateRight() { return bbActivateRight; }
	void setBBActivateRight(RECT bbActivateRight);
	void setBBPlayer(D3DXVECTOR4 bbPlayer);
	void  handleState();
	~Panther();
};

