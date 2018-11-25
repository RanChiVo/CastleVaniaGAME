#include "Heart.h"
#include "../ResourceManagement.h"
#include "../GameObjects/Simon.h"

constexpr int HEART_ANI_HIDE = 24;
constexpr int HEART_ANI_SHOW = 25;
constexpr float HEART_GRAVITY = 0.05f;

Heart::Heart()
{
}

Heart::Heart(D3DXVECTOR2 position)
{
	id = ID_TEX_HEART;
	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_HEART)->Get("Heart1")->getRect();
	int height = r.bottom - r.top;

	x = position.x;
	y = position.y;

	LPANIMATION ani;

	ani = new Animation(40);
	ani->Add("Heart1");
	Animations::GetInstance()->Add(HEART_ANI_HIDE, ani);

	ani = new Animation(40);
	ani->Add("Effect1");
	ani->Add("Effect2");
	ani->Add("Effect3");
	ani->Add("Effect4");
	ani->Add("Heart1");

	Animations::GetInstance()->Add(HEART_ANI_SHOW, ani);

	AddAnimation(HEART_ANI_HIDE);
	AddAnimation(HEART_ANI_SHOW);

	state = HEART_STATE_HIDE;
	currentAnimation = HEART_ANI_HIDE;
}

void Heart::Update(DWORD dt,  vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);

	if (state == HEART_STATE_HIDE)
	{
		currentAnimation = HEART_ANI_HIDE;
	}
	else if (state == HEART_STATE_SHOW)
	{
		currentAnimation = HEART_ANI_SHOW;

		if (animations.find(currentAnimation)->second->getCurrentFrame() == 4)

			animations.find(currentAnimation)->second->SetFinish1(true);

		vy += HEART_GRAVITY*dt ;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != HEART_STATE_HIDE)
			CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			y += min_ty * dy + ny * 0.4f;

			if (ny != 0) vy = 0;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

}

void Heart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_HEART)->Get("Heart1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height ;
}

void Heart::Render(Viewport * viewport)
{
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->Render(position.x, position.y);
}

Heart::~Heart()
{
}
