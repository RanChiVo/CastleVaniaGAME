#include "BurnBarrel.h"
#include "Simon.h"
#include "Whip.h"
#include "../Animations/Animations.h"
#include "../ResourceManagement.h"
constexpr int BURNBARREL_ANI = 14;

BurnBarrel::BurnBarrel()
{
}

BurnBarrel::BurnBarrel(D3DXVECTOR2 position)
{
	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_BURNBARREL)->Get("Burn1")->getRect();
	int height = r.bottom - r.top;

	x = position.x;
	y = position.y - height;

	LPANIMATION ani;

	ani = new Animation(150);
	ani->Add("Burn1");
	ani->Add("Burn2");

	Animations::GetInstance()->Add(BURNBARREL_ANI, ani);
	AddAnimation(BURNBARREL_ANI);
}

void BurnBarrel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (coEvents.size() == 0)
	{
		return;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//y += 10; x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		//y += min_ty * dy + ny * 0.4f;

		//if (nx != 0) vx = 0;
		//if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Whip *>(e->obj))
			{
				Whip  *whip = dynamic_cast<Whip *>(e->obj);
					if ((e->nx > 0) || (e->nx < 0))
					{
						y += 2;
					}
			}
		}
	}


	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void BurnBarrel::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_BURNBARREL)->Get("Burn1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

void BurnBarrel::Render(Viewport * viewport)
{
	currentAnimation = BURNBARREL_ANI;
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->SetLoop(true);

	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->Render(position.x, position.y);
}

BurnBarrel::~BurnBarrel()
{
}
