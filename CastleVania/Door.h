#pragma once
#include "./StaticObject.h"

class Door: public StaticObject
{
private:
	static DWORD action1Start;
	static DWORD action2Start;
	static DWORD action3Start;
	static DWORD action4Start;
	static DWORD action5Start;
	 
public:
	enum stateDoor
	{
		DOOR_STATE_CLOSE,
		DOOR_STATE_OPEN,
		DOOR_STATE_CLOSING,
		DOOR_STATE_OPENING,
	};
	Door(D3DXVECTOR2 position, int height, int width);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Viewport* viewport);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	static void startAction();
	void handleState();
	~Door();
};

