#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "../SpriteManagements/Sprite.h"
#include <string>

using namespace std;

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
class Animation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	bool isFinished = false;
	bool isLooped = true;
public:

	bool IsFinished();
	void SetLoop(bool loop);
	void SetFinish(bool finish);

	Animation(int defaultTime) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }

	int getCurrentFrame();
	void setCurrentFrame(int index);

	void Add(std::string  spriteId, DWORD time = 0);
	void Render(float x, float y, Flip flip);
	void update();
};

typedef Animation *LPANIMATION;
