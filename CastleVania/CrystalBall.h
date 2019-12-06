#pragma once
#include "CombatWeapon.h"

class CrystalBall : public CombatWeapon
{
private:
	DWORD timeShoot;
public:
	CrystalBall(D3DXVECTOR2 pos, int nx);
	void startShoot();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	~CrystalBall();
};

