#include "Animation.h"
#include "../SpriteManagements/Sprites.h"
#include "../Game.h"
#include "../DebugOut/DebugOut.h"


bool Animation::IsFinished()
{
	return isFinished;
}

void Animation::SetLoop(bool loop)
{
	isLooped = loop;
}

void Animation::SetFinish(bool finish)
{ 
	currentFrame = -1;
	isFinished = finish;
}

int Animation::getCurrentFrame()
{
	return currentFrame;
}

void Animation::setCurrentFrame(int index)
{
	currentFrame = index;
}

void Animation::Add(std::string spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
	isFinished = false;
}

void Animation::Render(float x, float y, Flip flip)
{
	DWORD now = GetTickCount();

	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else if (!isFinished)
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size())
			{
				if (isLooped == false) isFinished = true;
				currentFrame = 0;
			}
		}
	}
	frames[currentFrame]->GetSprite()->Draw(D3DXVECTOR2(x, y), flip);
}

void Animation::update()
{
}
