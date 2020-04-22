#pragma once
#include "GameObjects/GameObject.h"

class Crown : public GameObject
{
	int score = 0;
	bool isActivate = false;
	DWORD timeEffect = 0;
public:
	Crown(D3DXVECTOR2 position, int height, int width);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render(Viewport* viewport);
	void startAction();
	int getScore();
	void setTimeEffect(DWORD dt);
	~Crown();
};

