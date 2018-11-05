										#include "Animation.h"
#include "../SpriteManagements/Sprites.h"
#include "../Game.h"
#include "../DebugOut/DebugOut.h"

// Animation::loop = true -> walk
// Animation::loop = false -> attack, jump, sitdown
// Animation::completed = true if loop = false and frame = lastFrame
// Animation::completed = true -> Simon::SetState(IDLE)

void Animation::Rewind()
{
	currentFrame = 0;
}

void Animation::Add(std::string spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
	isCompleted = false;
}

bool Animation::Render(float x, float y, bool isLooped)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size())
			{
				Rewind();
				
				if(isLooped == false) isCompleted = true;
			}
			else {
				isCompleted = false;
			}
			
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}
	}

	frames[currentFrame]->GetSprite()->Draw(x, y);

	return isCompleted;
}

void Animation::update()
{
}
