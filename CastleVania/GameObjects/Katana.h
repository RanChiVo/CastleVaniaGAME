#pragma once
#include "../GameObjects/GameObject.h"

constexpr int  KATANA_STATE_HIDE = 1;
constexpr int  KATANA_STATE_SHOW = 2;
constexpr int  KATANA_ANI_HIDE = 22;
constexpr int  KATANA_ANI_SHOW = 23;
constexpr float KATANA_GRAVITY = 0.02f;


class Katana : public GameObject
{
public:
	Katana();
	Katana(D3DXVECTOR2 position);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) override;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	virtual void Render(Viewport* viewport);
	~Katana();
}; 

