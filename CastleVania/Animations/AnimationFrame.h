#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "../SpriteManagerments/Sprite.h"

class AnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	AnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef AnimationFrame *LPANIMATION_FRAME;
