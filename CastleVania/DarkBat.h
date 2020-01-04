#pragma once
#include "Enemy.h"
#include "BaseInfo.h"

class DarkBat : public Enemy
{
private:
	D3DXVECTOR2 originalLocation;
	int activatePositionMaxX;
	DWORD startTimeIdle = 0;
	DWORD startTimeMoveRandom = 0;
	DWORD startTimeActackPlayer = 0;
	DWORD startTimeEffect = 0;
	static bool isActivate;
	bool hasBeenActivate;
	static DWORD startTimeHurt;
	static BaseInfo  baseInfo;
public:
	enum stateDarkBat
	{
		DARK_BAT_STATE_MOVERANDOM,
		DARK_BAT_STATE_HURT,
		DARK_BAT_STATE_IDLE,
		DARK_BAT_STATE_EFFECT_DESTROY,
	};
	DarkBat(D3DXVECTOR2 pos );
	static BaseInfo getBaseInfo() { return baseInfo; }
    void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Viewport* viewport);
	void handleState();
	static void ActivateState() { isActivate = true; }
	static void StartTimeHurt() { startTimeHurt = GetTickCount(); }
	void handleMoveRandom();
	void changeMoveRandomToIdle();
	void changeActivateToMoveRandom();
	void changeIdleRandomToAtack();
	void changeAtackToMoveRandom();
	~DarkBat();
};

