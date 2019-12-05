#include "Effect.h"

constexpr float  EFFECT_GRAVITY =0.00025f;
constexpr int EFFECT_ALIVE_TIME = 2000;

Effect::Effect()
{
	liveTime = GetTickCount();
}

void Effect::Render(Viewport * viewport)
{
	for (int i = 0; i < totalEffect; i++)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(position_X[i], position_Y[i]));
		animations.find(currentAnimation)->second->Render(position.x, position.y, Flip::normal);
	}
}

void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < totalEffect; i++)
	{
		position_X[i] += speech_X[i] * dt;
		position_Y[i] += speech_Y[i] * dt;
		speech_Y[i] += EFFECT_GRAVITY * dt;
	}

	if (GetTickCount() - liveTime > EFFECT_ALIVE_TIME)
		state = STATE_DETROY;
}

void Effect::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

Effect::~Effect()
{
}
