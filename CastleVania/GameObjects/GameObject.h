#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "../Animations/Animation.h"

using namespace std;

class GameObject
{
protected:

	float x;
	float y;

	float vx;
	float vy;

	int nx;

	int state;
	
	static vector<LPANIMATION> animations;

public:
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
	virtual void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	
	virtual void SetState(int state) { this->state = state; }
	virtual int GetState() { return this->state; }
	virtual int GetDierection() { return this->nx; }
	static void AddAnimation(int aniId);
		//, std::vector<std::string> spriteIDs, int frameTimeout);
	GameObject();

	virtual void Update(DWORD dt);
	virtual void Render();
	virtual ~GameObject();
};