#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "AnimationFrame.h"

using namespace std;

class Animation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	Animation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y);
};

typedef Animation *LPANIMATION;
