#pragma once
#include "GameObjects/GameObject.h"

class Effect : public GameObject
{
protected:
	float* position_X;
	float* position_Y;
	float* speech_X;
	float* speech_Y;
	int totalEffect;
public:
	Effect();
	virtual void Render(Viewport* viewport);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~Effect();
};

